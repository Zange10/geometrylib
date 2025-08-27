#include "geometrylib_datatool.h"
#include <string.h>
#include <stdio.h>

#define DATA_ARRAY_STACK_LIMIT 128

typedef struct DataArray1 {
	double stack_buffer[DATA_ARRAY_STACK_LIMIT];
	double* data;
	size_t count;
	size_t capacity;
	bool using_heap;
} DataArray1;

typedef struct DataArray2 {
	Vector2 stack_buffer[DATA_ARRAY_STACK_LIMIT];
	Vector2* data;
	size_t count;
	size_t capacity;
	bool using_heap;
} DataArray2;

typedef struct DataArray3 {
	Vector3 stack_buffer[DATA_ARRAY_STACK_LIMIT];
	Vector3* data;
	size_t count;
	size_t capacity;
	bool using_heap;
} DataArray3;

typedef struct DataArrayN {
	double** data;
	int dimensions;
	size_t count;
	size_t capacity;
} DataArrayN;


size_t data_array1_size(DataArray1 *arr) {return arr->count;}
size_t data_array2_size(DataArray2 *arr) {return arr->count;}
size_t data_array3_size(DataArray3 *arr) {return arr->count;}
size_t data_arrayn_size(DataArrayN *arr) {return arr->count;}

double  * data_array1_get_data(DataArray1 *arr) {return arr->data;}
Vector2 * data_array2_get_data(DataArray2 *arr) {return arr->data;}
Vector3 * data_array3_get_data(DataArray3 *arr) {return arr->data;}
double ** data_arrayn_get_data(DataArrayN *arr) {return arr->data;}

DataArray1 * data_array1_create() {
	DataArray1* arr = malloc(sizeof(DataArray1));
	arr->data = arr->stack_buffer;
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	arr->using_heap = false;
	return arr;
}

DataArray2 * data_array2_create() {
	DataArray2* arr = malloc(sizeof(DataArray2));
	arr->data = arr->stack_buffer;
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	arr->using_heap = false;
	return arr;
}

DataArray3 * data_array3_create() {
	DataArray3* arr = malloc(sizeof(DataArray3));
	arr->data = arr->stack_buffer;
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	arr->using_heap = false;
	return arr;
}

DataArrayN * data_arrayn_create(int dimensions) {
	DataArrayN* arr = malloc(sizeof(DataArray3));
	arr->data = malloc(DATA_ARRAY_STACK_LIMIT*sizeof(double*));
	arr->dimensions = dimensions;
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	for(int i = 0; i < arr->capacity; i++) arr->data[i] = malloc(dimensions*sizeof(double));
	return arr;
}

void data_array1_free(DataArray1* arr) {
	if(!arr) return;
	if(arr->using_heap) free(arr->data);
	free(arr);
}

void data_array2_free(DataArray2* arr) {
	if(!arr) return;
	if(arr->using_heap) free(arr->data);
	free(arr);
}

void data_array3_free(DataArray3* arr) {
	if(!arr) return;
	if(arr->using_heap) free(arr->data);
	free(arr);
}

void data_arrayn_free(DataArrayN* arr) {
	if (!arr) return;
	for(int i = 0; i < arr->capacity; i++) free(arr->data[i]);
	free(arr->data);
	free(arr);
}

void check_data_array1_add_capacity(DataArray1 *arr) {
	if(arr->count >= arr->capacity) {
		size_t new_capacity = arr->capacity * 2;
		double *new_data = malloc(new_capacity * sizeof(double));
		memcpy(new_data, arr->data, arr->count * sizeof(double));
		if(arr->using_heap) free(arr->data);
		arr->data = new_data;
		arr->capacity = new_capacity;
		arr->using_heap = true;
	}
}

void check_data_array2_add_capacity(DataArray2 *arr) {
	if(arr->count >= arr->capacity) {
		size_t new_capacity = arr->capacity * 2;
		Vector2 *new_data = malloc(new_capacity * sizeof(Vector2));
		memcpy(new_data, arr->data, arr->count * sizeof(Vector2));
		if(arr->using_heap) free(arr->data);
		arr->data = new_data;
		arr->capacity = new_capacity;
		arr->using_heap = true;
	}
}

void check_data_array3_add_capacity(DataArray3 *arr) {
	if(arr->count >= arr->capacity) {
		size_t new_capacity = arr->capacity * 2;
		Vector3 *new_data = malloc(new_capacity * sizeof(Vector3));
		memcpy(new_data, arr->data, arr->count * sizeof(Vector3));
		if(arr->using_heap) free(arr->data);
		arr->data = new_data;
		arr->capacity = new_capacity;
		arr->using_heap = true;
	}
}

void check_data_arrayn_add_capacity(DataArrayN *arr) {
	if(arr->count >= arr->capacity) {
		size_t new_capacity = arr->capacity * 2;
		double **new_data = malloc(new_capacity * sizeof(double *));
		memcpy(new_data, arr->data, arr->count * sizeof(double *));
		for(int i = (int)arr->count; i < new_capacity; i++) new_data[i] = malloc(arr->dimensions*sizeof(double));
		free(arr->data);
		arr->data = new_data;
		arr->capacity = new_capacity;
	}
}

void data_array1_append_new(DataArray1 *arr, double value) {
	check_data_array1_add_capacity(arr);
	arr->data[arr->count++] = value;
}

void data_array2_append_new(DataArray2 *arr, double x, double y) {
	check_data_array2_add_capacity(arr);
	arr->data[arr->count++] = (Vector2){x,y};
}

void data_array3_append_new(DataArray3 *arr, double x, double y, double z) {
	check_data_array3_add_capacity(arr);
	arr->data[arr->count++] = (Vector3){x,y,z};
}

void data_arrayn_append_new_from_values(DataArrayN *arr, double *values) {
	check_data_arrayn_add_capacity(arr);
	for(int i = 0; i < arr->dimensions; i++) arr->data[arr->count][i] = values[i];
	arr->count++;
}

void data_arrayn_append_new_from_pointers(DataArrayN *arr, double **p_values) {
	check_data_arrayn_add_capacity(arr);
	for(int i = 0; i < arr->dimensions; i++) arr->data[arr->count][i] = *(p_values[i]);
	arr->count++;
}


void data_array2_insert_new(DataArray2 *arr, double x, double y) {
	check_data_array2_add_capacity(arr);
	size_t insert_index = arr->count;
	
	for (size_t i = 0; i < arr->count; i++) {
		if (arr->data[i].x > x) {
			insert_index = i; break;
		}
	}
	
	if (insert_index < arr->count) {
		memmove(&arr->data[insert_index + 1],
				&arr->data[insert_index],
				(arr->count - insert_index) * sizeof(Vector2));
	}
	
	arr->data[insert_index] = (Vector2){x, y};
	arr->count++;
}

double root_finder_monot_func_next_x(DataArray2 *arr) {
	// branch = 0 for decreasing monotonously, 1 for increasing monotonously
	if(arr->count == 2) return (arr->data[0].x + arr->data[1].x)/2;
	int num_data = (int) arr->count;
	int i_n = 1, i_p = 1;	// negative and positive index
	bool increasing = true;
	if(arr->data[0].y > arr->data[1].y) increasing = false;
	
	if(increasing) {
		for(int i = 1; i < num_data; i++) {
			if(arr->data[i].y > 0)			{ i_p = i; break; }
		}
		i_n = i_p-1;
	} else {
		for(int i = 1; i < num_data; i++) {
			if(arr->data[i].y < 0)			{ i_n = i; break; }
		}
		i_p = i_n-1;
	}
	if(i_p == 0 || i_p == num_data-1 ||
	   i_n == 0 || i_n == num_data-1) return (arr->data[i_p].x+arr->data[i_n].x) / 2;
	
	
	double m = (arr->data[i_n].y - arr->data[i_p].y) / (arr->data[i_n].x - arr->data[i_p].x);
	double n = arr->data[i_p].y - arr->data[i_p].x*m;
	
	return -n/m;
}

Vector2 get_xn(Vector2 d0, Vector2 d1, double m_l, double m_r) {
	Vector2 xn;
	xn.x = (d1.y-d0.y + m_l*d0.x - m_r*d1.x) / (m_l-m_r);
	xn.y = m_l * (xn.x-d0.x) + d0.y;
	return xn;
}

double root_finder_monot_deriv_next_x(DataArray2 *arr, int branch) {
	// branch = 0 for left branch, 1 for right branch
	if(arr->count == 2) return (arr->data[0].x + arr->data[1].x)/2;
	int num_data = (int) arr->count;
	int index;
	
	// left branch
	if(branch == 0) {
		index = 1;
		for(int i = 1; i <= num_data; i++) {
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
		if(branch == 0) return (arr->data[index].x + arr->data[index-1].x)/2;
		else 			return (arr->data[index].x + arr->data[index+1].x)/2;
	}
	
	if(index <= 2)			return (arr->data[1].x + arr->data[2].x)/2;
	if(index >= num_data-1)	return (arr->data[num_data-1].x + arr->data[num_data].x)/2;
	
	
	double gradient_l 	= (arr->data[index  ].y - arr->data[index - 1].y) / (arr->data[index  ].x - arr->data[index - 1].x);
	double gradient_r 	= (arr->data[index  ].y - arr->data[index + 1].y) / (arr->data[index  ].x - arr->data[index + 1].x);
	double gradient_ll 	= (arr->data[index-1].y - arr->data[index - 2].y) / (arr->data[index-1].x - arr->data[index - 2].x);
	double gradient_rr 	= (arr->data[index+1].y - arr->data[index + 2].y) / (arr->data[index+1].x - arr->data[index + 2].x);
	
	Vector2 xn_l = get_xn(arr->data[index-1], arr->data[index  ], gradient_ll, gradient_r);
	Vector2 xn_r = get_xn(arr->data[index  ], arr->data[index+1], gradient_l, gradient_rr);
	
	return (xn_l.y < xn_r.y) ? xn_l.x : xn_r.x;
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

void print_data_array2(DataArray2 *arr, const char *x_name, const char *y_name) {
	printf("%s = [", x_name);
	for(int j = 0; j < arr->count; j++) {
		if(j!=0) printf(", ");
		printf("%g", arr->data[j].x);
	}
	printf("]\n%s = [", y_name);
	for(int j = 0; j < arr->count; j++) {
		if(j!=0) printf(", ");
		printf("%g", arr->data[j].y);
	}
	printf("]\n");
}

void print_data_array3(DataArray3 *arr, const char *x_name, const char *y_name, const char *z_name) {
	printf("%s = [", x_name);
	for(int j = 0; j < arr->count; j++) {
		if(j!=0) printf(", ");
		printf("%g", arr->data[j].x);
	}
	printf("]\n%s = [", y_name);
	for(int j = 0; j < arr->count; j++) {
		if(j!=0) printf(", ");
		printf("%g", arr->data[j].y);
	}
	printf("]\n%s = [", z_name);
	for(int j = 0; j < arr->count; j++) {
		if(j!=0) printf(", ");
		printf("%g", arr->data[j].z);
	}
	printf("]\n");
}

void print_data_arrayN(DataArrayN *arr, const char **name) {
	for(int i = 0; i < arr->dimensions; i++) {
		if(i==0) printf("x%d = [", i);
		else 	 printf("]\nx%d = [", i);
		for(int j = 0; j < arr->count; j++) {
			if(j!=0) printf(", ");
			printf("%g", arr->data[j][i]);
		}
	}
}
