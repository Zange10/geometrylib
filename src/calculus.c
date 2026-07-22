#include <math.h>
#include <stdio.h>

#include "geometrylib_calculus.h"
#include "data_array_def.h"
#include "geometrylib_linetool.h"

double get_y_value_from_x_value_of_line(Vector2 p0, Vector2 p1, double x) {
	double m = (p1.y - p0.y)/(p1.x - p0.x);
	double y = (x - p0.x)*m + p0.y;
	return y;
}

double get_x_value_from_y_value_of_line(Vector2 p0, Vector2 p1, double y) {
	double m = (p1.y - p0.y)/(p1.x - p0.x);
	double x = (y - p0.y)/m + p0.x;
	return x;
}

double get_single_root_of_line_array(DataArray2 *arr) {
	if(!arr || arr->data[0].y > 0 == arr->data[arr->count-1].y > 0) return NAN;
	int idx0 = 0, idx1 = (int) arr->count-1;

	while(idx1-idx0 > 1) {
		int idx_m = (idx0 + idx1)/2;
		if(arr->data[idx_m].y < 0 == arr->data[idx0].y < 0) idx0 = idx_m;
		else idx1 = idx_m;
	}

	return get_x_value_from_y_value_of_line(arr->data[idx0], arr->data[idx1], 0);
}

DataArray1 * data_array1_get_diff(DataArray1 *arr) {
	if(!arr) return NULL;
	DataArray1 *diff = data_array1_create();

	for(int i = 0; i < arr->count-1; i++) {
		data_array1_append_new(diff, arr->data[i+1]-arr->data[i]);
	}

	return diff;
}

DataArray2 * data_array2_get_gradient(DataArray2 *arr) {
	if(!arr) return NULL;
	DataArray2 *gradient = data_array2_create();

	for(int i = 0; i < arr->count-1; i++) {
		data_array2_append_new(gradient,
			vec2(
				(arr->data[i].x+arr->data[i+1].x)/2,
				(arr->data[i+1].y-arr->data[i].y)/(arr->data[i+1].x-arr->data[i].x)
				));
	}

	return gradient;
}

double get_next_x_for_root_search_from_line(Vector2 p0, Vector2 p1, double min_diff_ratio, double min_dx) {
	if(p0.x == p1.x || p0.y < 0 == p1.y < 0) return NAN;

	double xdiff = p1.x - p0.x;
	if(xdiff/2 < min_dx) return NAN;
	if(xdiff*min_diff_ratio < min_dx) min_diff_ratio = min_dx/xdiff;

	double x_at_root = get_x_value_from_y_value_of_line(p0, p1, 0);
	double d_root = x_at_root-p0.x;
	double diff_ratio = d_root/xdiff;

	if(diff_ratio < min_diff_ratio) return p0.x + xdiff*min_diff_ratio;
	if(diff_ratio > 1-min_diff_ratio) return p1.x - xdiff*min_diff_ratio;
	return p0.x + xdiff*diff_ratio;
}

double root_finder_monot_func_next_x(DataArray2 *arr, double min_diff_ratio, double min_dx) {
	if(arr->count < 2) return NAN;
	if(arr->data[0].y < 0 == arr->data[arr->count-1].y < 0) return NAN;
	if(arr->count == 2) return (arr->data[0].x + arr->data[1].x)/2;
	int idx0 = 0, idx1 = (int) arr->count-1;

	while(idx1-idx0 > 1) {
		int idx_m = (idx0 + idx1)/2;
		if(arr->data[idx_m].y < 0 == arr->data[idx0].y < 0) idx0 = idx_m;
		else idx1 = idx_m;
	}

	if(idx0 == 0) return arr->data[idx0].x + (arr->data[idx1].x - arr->data[idx0].x) / 4;
	if(idx1 == arr->count-1) return arr->data[idx1].x - (arr->data[idx1].x - arr->data[idx0].x) / 4;

	return get_next_x_for_root_search_from_line(arr->data[idx0], arr->data[idx1], min_diff_ratio, min_dx);
}

int get_idx_of_unimodal_func_minimum(DataArray2 *arr) {
	if(arr->count == 0) return NAN;
	if(arr->count == 1 || arr->data[0].y < arr->data[1].y) return 0;
	if(arr->data[arr->count-1].y < arr->data[arr->count-2].y) return (int) arr->count-1;

	int idx0 = 0, idx1 = (int) arr->count - 1, idx_min = -1;

	while(idx0 < idx1-1) {
		int idx_m = (idx0 + idx1)/2;
		if(arr->data[idx_m].y < arr->data[idx_m-1].y && arr->data[idx_m].y < arr->data[idx_m+1].y) {
			idx_min = idx_m; break;
		}

		if(arr->data[idx_m].y < arr->data[idx_m-1].y) idx0 = idx_m;
		else idx1 = idx_m;
	}

	if(idx_min < 0) idx_min = arr->data[idx0].y < arr->data[idx1].y ? idx0 : idx1;

	return idx_min;
}

int get_idx_of_unimodal_func_maximum(DataArray2 *arr) {
	if(arr->count == 0) return NAN;
	if(arr->count == 1 || arr->data[0].y > arr->data[1].y) return 0;
	if(arr->data[arr->count-1].y > arr->data[arr->count-2].y) return (int) arr->count-1;

	int idx0 = 0, idx1 = (int) arr->count - 1, idx_max = -1;

	while(idx0 < idx1-1) {
		int idx_m = (idx0 + idx1)/2;
		if(arr->data[idx_m].y > arr->data[idx_m-1].y && arr->data[idx_m].y > arr->data[idx_m+1].y) {
			idx_max = idx_m; break;
		}

		if(arr->data[idx_m].y > arr->data[idx_m-1].y) idx0 = idx_m;
		else idx1 = idx_m;
	}

	if(idx_max < 0) idx_max = arr->data[idx0].y > arr->data[idx1].y ? idx0 : idx1;

	return idx_max;
}

Vector2 get_xn(Vector2 d0, Vector2 d1, double m_l, double m_r) {
	Vector2 xn;
	xn.x = (d1.y-d0.y + m_l*d0.x - m_r*d1.x) / (m_l-m_r);
	xn.y = m_l * (xn.x-d0.x) + d0.y;
	return xn;
}

double root_finder_monot_deriv_next_x(DataArray2 *arr, bool right_branch) {
	// branch = 0 for left branch, 1 for right branch
	if(arr->count == 2) return (arr->data[0].x + arr->data[1].x)/2;
	int num_data = (int) arr->count;
	int index;

	// left branch
	if(!right_branch) {
		index = 0;
		for(int i = 1; i < num_data; i++) {
			if(arr->data[i].y < 0)					{ index = i; break; }
			if(arr->data[i].y > arr->data[i-1].y)	{ break; }
			else 									{ index = i; }
		}

		// right branch
	} else {
		index = num_data-1;
		for(int i = num_data-2; i >= 0; i--) {
			if(arr->data[i].y < 0)					{ index =   i; break; }
			if(arr->data[i].y > arr->data[i+1].y)	{ index = 1+i; break; }
			else 									{ index =   i; }
		}
	}

	if(arr->data[index].y < 0) {
		if(!right_branch) return (arr->data[index].x + arr->data[index-1].x)/2;
		else 			return (arr->data[index].x + arr->data[index+1].x)/2;
	}

	if(index <= 1)			return (arr->data[0].x + arr->data[1].x)/2;
	if(index >= num_data-2)	return (arr->data[num_data-2].x + arr->data[num_data-1].x)/2;


	double gradient_l 	= (arr->data[index  ].y - arr->data[index - 1].y) / (arr->data[index  ].x - arr->data[index - 1].x);
	double gradient_r 	= (arr->data[index  ].y - arr->data[index + 1].y) / (arr->data[index  ].x - arr->data[index + 1].x);
	double gradient_ll 	= (arr->data[index-1].y - arr->data[index - 2].y) / (arr->data[index-1].x - arr->data[index - 2].x);
	double gradient_rr 	= (arr->data[index+1].y - arr->data[index + 2].y) / (arr->data[index+1].x - arr->data[index + 2].x);

	Vector2 xn_l = get_xn(arr->data[index-1], arr->data[index  ], gradient_ll, gradient_r);
	Vector2 xn_r = get_xn(arr->data[index  ], arr->data[index+1], gradient_l, gradient_rr);

	return (xn_l.y < xn_r.y) ? xn_l.x : xn_r.x;
}

double get_next_x_for_min_search(DataArray2 *arr, int min_idx, double min_diff_ratio, double min_dx) {
	if(min_idx < 0 || min_idx >= arr->count) min_idx = get_idx_of_unimodal_func_minimum(arr);

	if(min_idx <= 1) {
		if(arr->data[1].x - arr->data[0].x < min_dx) return NAN;
		return arr->data[0].x + (arr->data[1].x-arr->data[0].x)*min_diff_ratio;
	}
	if(min_idx >= arr->count-2) {
		if(arr->data[arr->count-1].x - arr->data[arr->count-2].x < min_dx) return NAN;
		return arr->data[arr->count-1].x - (arr->data[arr->count-1].x-arr->data[arr->count-2].x)*min_diff_ratio;
	}

	Vector2 p0, p1, p2, p3;

	double diff_xl = arr->data[min_idx].x - arr->data[min_idx-1].x;
	double diff_xr = arr->data[min_idx+1].x - arr->data[min_idx].x;
	if(diff_xl > diff_xr) {
		p0 = arr->data[min_idx-2];
		p1 = arr->data[min_idx-1];
		p2 = arr->data[min_idx  ];
		p3 = arr->data[min_idx+1];
	} else {
		p0 = arr->data[min_idx-1];
		p1 = arr->data[min_idx  ];
		p2 = arr->data[min_idx+1];
		p3 = arr->data[min_idx+2];
	}

	double xdiff = p2.x - p1.x;
	if(xdiff/2 < min_dx) return NAN;
	if(xdiff*min_diff_ratio < min_dx) min_diff_ratio = min_dx/xdiff;

	double m_l = (p1.y - p0.y) / (p1.x - p0.x);
	double m_r = (p3.y - p2.y) / (p3.x - p2.x);

	double diff_ratio;
	if(-m_l/m_r > 1) {
		double m_ratio = -m_r/m_l;
		diff_ratio = m_ratio/2;
	} else {
		double m_ratio = -m_l/m_r;
		diff_ratio = 1-m_ratio/2;
	}

	if(diff_ratio < min_diff_ratio) return p1.x + xdiff*min_diff_ratio;
	if(diff_ratio > 1-min_diff_ratio) return p2.x - xdiff*min_diff_ratio;
	return p1.x + xdiff*diff_ratio;
}

double get_next_x_for_max_search(DataArray2 *arr, int max_idx, double min_diff_ratio, double min_dx) {
	if(max_idx < 0 || max_idx >= arr->count) max_idx = get_idx_of_unimodal_func_maximum(arr);

	if(max_idx <= 1) return arr->data[0].x + (arr->data[1].x-arr->data[0].x)*min_diff_ratio;
	if(max_idx >= arr->count-2) return arr->data[arr->count-1].x - (arr->data[arr->count-1].x-arr->data[arr->count-2].x)*min_diff_ratio;

	Vector2 p0, p1, p2, p3;

	double diff_xl = arr->data[max_idx].x - arr->data[max_idx-1].x;
	double diff_xr = arr->data[max_idx+1].x - arr->data[max_idx].x;
	if(diff_xl > diff_xr) {
		p0 = arr->data[max_idx-2];
		p1 = arr->data[max_idx-1];
		p2 = arr->data[max_idx  ];
		p3 = arr->data[max_idx+1];
	} else {
		p0 = arr->data[max_idx-1];
		p1 = arr->data[max_idx  ];
		p2 = arr->data[max_idx+1];
		p3 = arr->data[max_idx+2];
	}

	double xdiff = p2.x - p1.x;
	if(xdiff/2 < min_dx) return NAN;
	if(xdiff*min_diff_ratio < min_dx) min_diff_ratio = min_dx/xdiff;

	double m_l = (p1.y - p0.y) / (p1.x - p0.x);
	double m_r = (p3.y - p2.y) / (p3.x - p2.x);

	double diff_ratio;
	if(-m_l/m_r > 1) {
		double m_ratio = -m_r/m_l;
		diff_ratio = m_ratio/2;
	} else {
		double m_ratio = -m_l/m_r;
		diff_ratio = 1-m_ratio/2;
	}

	if(diff_ratio < min_diff_ratio) return p1.x + xdiff*min_diff_ratio;
	if(diff_ratio > 1-min_diff_ratio) return p2.x - xdiff*min_diff_ratio;
	return p1.x + xdiff*diff_ratio;
}

double min_achievable_value_from_prev_and_next_points(DataArray2 *arr, int min_idx, int num_point_range) {
	if(min_idx < 0 || min_idx >= arr->count) min_idx = get_idx_of_unimodal_func_minimum(arr);
	if(min_idx < num_point_range || min_idx+num_point_range > arr->count-1) return NAN;

	double min_y = NAN;
	for(int i = -num_point_range; i < num_point_range; i++) {
		if(min_idx+i < 0 || min_idx+i+1 >= arr->count) continue;
		double y;
		if(i == -1 || i == 0) {
			y = arr->data[min_idx].y;
		} else {
			Vector2 p0 = arr->data[min_idx+i];
			Vector2 p1 = arr->data[min_idx+i+1];
			y = get_y_value_from_x_value_of_line(p0, p1, arr->data[min_idx].x);
		}
		if(isnan(min_y) || y < min_y) min_y = y;
	}

	return min_y;
}

double max_achievable_value_from_prev_and_next_points(DataArray2 *arr, int max_idx, int num_point_range) {
	if(max_idx < 0 || max_idx >= arr->count) max_idx = get_idx_of_unimodal_func_maximum(arr);
	if(max_idx < num_point_range || max_idx+num_point_range > arr->count-1) return NAN;

	double max_y = NAN;
	for(int i = -num_point_range; i < num_point_range; i++) {
		if(max_idx+i < 0 || max_idx+i+1 >= arr->count) continue;
		double y;
		if(i == -1 || i == 0) {
			y = arr->data[max_idx].y;
		} else {
			Vector2 p0 = arr->data[max_idx+i];
			Vector2 p1 = arr->data[max_idx+i+1];
			y = get_y_value_from_x_value_of_line(p0, p1, arr->data[max_idx].x);
		}
		if(isnan(max_y) || y > max_y) max_y = y;
	}

	return max_y;
}

double root_finder_single_minimum_func_next_x(DataArray2 *arr, bool left_branch, double min_diff_ratio, double min_dx) {
	if(arr->count < 2) return NAN;
	if(arr->count == 2) return (arr->data[0].x + arr->data[1].x)/2;

	if(left_branch  && arr->data[0].y < 0) return NAN;
	if(!left_branch && arr->data[arr->count-1].y < 0) return NAN;

	int min_idx = get_idx_of_unimodal_func_minimum(arr);

	if(arr->data[min_idx].y > 0) {
		if((min_idx == 0 || min_idx == arr->count-1) && arr->count >= 10) return NAN;

		int min_point_range = 2;
		if(min_idx > min_point_range && min_idx+min_point_range < arr->count) {
			double min_y = min_achievable_value_from_prev_and_next_points(arr, min_idx, min_point_range);
			if(min_y > 0) return NAN;
		}
		return get_next_x_for_min_search(arr, min_idx, min_diff_ratio, min_dx);
	}

	int idx0, idx1;
	if(left_branch) {
		idx0 = 0, idx1 = min_idx;
		while(idx1-idx0 > 1) {
			int idx_m = (idx0 + idx1)/2;
			if(arr->data[idx_m].y > 0) idx0 = idx_m;
			else idx1 = idx_m;
		}
		if(idx0 <= 1) return arr->data[0].x + (arr->data[1].x-arr->data[0].x)*min_diff_ratio;
	} else {
		idx0 = min_idx, idx1 = (int) arr->count-1;
		while(idx1-idx0 > 1) {
			int idx_m = (idx0 + idx1)/2;
			if(arr->data[idx_m].y < 0) idx0 = idx_m;
			else idx1 = idx_m;
		}
		if(idx1 >= arr->count-2) return arr->data[arr->count-1].x - (arr->data[arr->count-1].x-arr->data[arr->count-2].x)*min_diff_ratio;
	}

	return get_next_x_for_root_search_from_line(arr->data[idx0], arr->data[idx1], min_diff_ratio, min_dx);
}

int can_be_negative_monot_deriv(DataArray2 *arr) {
	int num_data = (int) arr->count;
	if(num_data < 3) return 1;

	int mind = 0;
	double min = arr->data[0].y;
	for(int i = 1; i < num_data; i++) {
		if(arr->data[i].y < min) { mind = i; min = arr->data[i].y; }
		if(min < 0) return 1;
	}

	if(mind == 0) mind++;
	if(mind == num_data-1) mind--;

	// gradient on left side and see whether it can get negative on right side
	double gradient = (arr->data[mind].y - arr->data[mind - 1].y) / (arr->data[mind].x - arr->data[mind - 1].x);
	double dx = arr->data[mind+1].x - arr->data[mind].x;
	if(gradient*dx + arr->data[mind].y < 0) return 1;

	// gradient on right side and see whether it can get negative on left side
	gradient = (arr->data[mind].y - arr->data[mind + 1].y) / (arr->data[mind].x - arr->data[mind + 1].x);
	dx = arr->data[mind-1].x - arr->data[mind].x;
	if(gradient*dx +arr-> data[mind].y < 0) return 1;

	return 0;
}
