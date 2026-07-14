#include <math.h>

#include "geometrylib_linetool.h"
#include "data_array_def.h"

double interpolate_from_sorted_data_array2(DataArray2 *data_array, double x) {
	Vector2 *data = data_array2_get_data(data_array);
	size_t num_data = data_array2_size(data_array);
	if(x < data[0].x || x > data[num_data-1].x) return NAN;

	int idx0 = 0, idx1 = (int) data_array->count-1;
	while(idx1-idx0 > 1) {
		int idx_m = (idx0 + idx1)/2;
		if(data_array->data[idx_m].x < x == data_array->data[idx0].y < x) idx0 = idx_m;
		else idx1 = idx_m;
	}

	Vector2 p0 = data[idx0], p1 = data[idx1];

	double m = (p1.y-p0.y) / (p1.x-p0.x);
	return (x-p0.x) * m + p0.y;
}

DataArray2 * get_line_intersections(DataArray2 *line0, DataArray2 *line1) {
	size_t size0 = data_array2_size(line0);
	size_t size1 = data_array2_size(line1);
	DataArray2 *inters_points = data_array2_create();

	if(size0 == 0 || size1 == 0) return inters_points;

	int init_j = 0;

	for(int i = 0; i < size0-1; i++) {
		for(int j = init_j; j < size1-1; j++) {
			if(are_line_segments_intersecting2(line0->data[i], line0->data[i+1], line1->data[j], line1->data[j+1])) {
				Vector2 u0 = line0->data[i];
				Vector2 u1 = line0->data[i+1];
				Vector2 v0 = line1->data[j];
				Vector2 v1 = line1->data[j+1];

				double m0 = (u1.y - u0.y)/(u1.x - u0.x);
				double m1 = (v1.y - v0.y)/(v1.x - v0.x);

				double n0 = u0.y - m0*u0.x;
				double n1 = v0.y - m1*v0.x;
				double x_inters = (n0-n1)/(m1-m0);
				double y_inters = m0*x_inters + n0;
				data_array2_append_new(inters_points, vec2(x_inters, y_inters));
			}
		}
	}

	return inters_points;
}
