#include <math.h>

#include "geometrylib_datatool.h"
#include "data_array_def.h"
#include <string.h>
#include <stdio.h>


size_t data_array1_size(DataArray1 *arr) {return arr->count;}
size_t data_array2_size(DataArray2 *arr) {return arr->count;}
size_t data_array3_size(DataArray3 *arr) {return arr->count;}
size_t data_arrayn_size(DataArrayN *arr) {return arr->count;}
size_t data_arrayn_num_dimensions(DataArrayN *arr) {return arr->dimensions;}

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
	DataArrayN* arr = malloc(sizeof(DataArrayN));
	arr->data = malloc(DATA_ARRAY_STACK_LIMIT*sizeof(double*));
	arr->dimensions = dimensions;
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	for(int i = 0; i < arr->capacity; i++) arr->data[i] = malloc(dimensions*sizeof(double));
	return arr;
}

void data_array1_clear(DataArray1 *arr) {
	if(!arr) return;
	if(arr->using_heap) free(arr->data);
	arr->data = arr->stack_buffer;
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	arr->using_heap = false;
}

void data_array2_clear(DataArray2 *arr) {
	if(!arr) return;
	if(arr->using_heap) free(arr->data);
	arr->data = arr->stack_buffer;
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	arr->using_heap = false;
}

void data_array3_clear(DataArray3 *arr) {
	if(!arr) return;
	if(arr->using_heap) free(arr->data);
	arr->data = arr->stack_buffer;
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	arr->using_heap = false;
}

void data_arrayn_clear(DataArrayN *arr) {
	if(!arr) return;
	for(int i = 0; i < arr->capacity; i++) free(arr->data[i]);
	free(arr->data);
	arr->data = malloc(DATA_ARRAY_STACK_LIMIT*sizeof(double*));
	arr->count = 0;
	arr->capacity = DATA_ARRAY_STACK_LIMIT;
	for(int i = 0; i < arr->capacity; i++) arr->data[i] = malloc(arr->dimensions*sizeof(double));
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
	if(!arr) return;
	for(int i = 0; i < arr->capacity; i++) free(arr->data[i]);
	free(arr->data);
	free(arr);
}

double data_array1_get(DataArray1 *arr, int idx) {
	if(arr->count == 0) return NAN;
	if(idx < 0 || idx > arr->count-1) return arr->data[arr->count-1];
	return arr->data[idx];
}

Vector2 data_array2_get(DataArray2 *arr, int idx) {
	if(arr->count == 0) return vec2(NAN, NAN);
	if(idx < 0 || idx > arr->count-1) return arr->data[arr->count-1];
	return arr->data[idx];
}

Vector3 data_array3_get(DataArray3 *arr, int idx) {
	if(arr->count == 0) return vec3(NAN, NAN, NAN);
	if(idx < 0 || idx > arr->count-1) return arr->data[arr->count-1];
	return arr->data[idx];
}

double *data_arrayn_get(DataArrayN *arr, int idx) {
	if(arr->count == 0) return NULL;
	if(idx < 0 || idx > arr->count-1) return arr->data[arr->count-1];
	return arr->data[idx];
}

DataArray1 *data_array1_slice(DataArray1 *arr, int start, int end) {
	if(start < 0 || start > arr->count-1) return NULL;
	if(end < 0 || end > arr->count-1) end = (int) arr->count-1;
	if(start > end) return NULL;

	DataArray1 *slice = data_array1_create();
	int num_elem = end-start+1;

	if(num_elem > DATA_ARRAY_STACK_LIMIT) {
		slice->capacity = num_elem;
		slice->data = malloc(num_elem * sizeof(double));
		slice->using_heap = true;
	}
	memcpy(slice->data, arr->data+start, num_elem*sizeof(double));
	slice->count = num_elem;

	return slice;
}

DataArray2 *data_array2_slice(DataArray2 *arr, int start, int end) {
	if(start < 0 || start > arr->count-1) return NULL;
	if(end < 0 || end > arr->count-1) end = (int) arr->count-1;
	if(start > end) return NULL;

	DataArray2 *slice = data_array2_create();
	int num_elem = end-start+1;

	if(num_elem > DATA_ARRAY_STACK_LIMIT) {
		slice->capacity = num_elem;
		slice->data = malloc(num_elem * sizeof(Vector2));
		slice->using_heap = true;
	}
	memcpy(slice->data, arr->data+start, num_elem*sizeof(Vector2));
	slice->count = num_elem;

	return slice;
}

DataArray3 *data_array3_slice(DataArray3 *arr, int start, int end) {
	if(start < 0 || start > arr->count-1) return NULL;
	if(end < 0 || end > arr->count-1) end = (int) arr->count-1;
	if(start > end) return NULL;

	DataArray3 *slice = data_array3_create();
	int num_elem = end-start+1;

	if(num_elem > DATA_ARRAY_STACK_LIMIT) {
		slice->capacity = num_elem;
		slice->data = malloc(num_elem * sizeof(Vector3));
		slice->using_heap = true;
	}
	memcpy(slice->data, arr->data+start, num_elem*sizeof(Vector3));
	slice->count = num_elem;

	return slice;
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

void data_array2_append_new(DataArray2 *arr, Vector2 value) {
	check_data_array2_add_capacity(arr);
	arr->data[arr->count++] = value;
}

void data_array3_append_new(DataArray3 *arr, Vector3 value) {
	check_data_array3_add_capacity(arr);
	arr->data[arr->count++] = value;
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

int data_array1_idx_from_binary_search(DataArray1 *arr, double value) {
	if(!arr->data || arr->count == 0) return 0;
	if(value <= arr->data[0]) return 0;
	if(value > arr->data[arr->count - 1]) return (int) arr->count;

	int idx0 = 0, idx1 = (int) arr->count - 1;

	while(idx0 != idx1) {
		// + 1 to ceil and not floor if necessary (first idx already checked, last index not)
		int idx_m = (idx0 + idx1 + 1)/2;
		if(value <= arr->data[idx_m] && value > arr->data[idx_m-1]) return idx_m;

		if(value > arr->data[idx_m]) idx0 = idx_m;
		else idx1 = idx_m;
	}

	return 0;
}

int data_array2_idx_from_binary_search(DataArray2 *arr, Vector2 value) {
	if(!arr->data || arr->count == 0) return 0;
	if(value.x < arr->data[0].x) return 0;
	if(value.x > arr->data[arr->count - 1].x) return (int) arr->count;

	int ins_idx = -1;
	if(value.x == arr->data[0].x) ins_idx = 0;

	int idx0 = 0, idx1 = (int) arr->count - 1;

	while(ins_idx < 0) {
		// + 1 to ceil and not floor if necessary (first idx already checked, last index not)
		int idx_m = (idx0 + idx1 + 1)/2;
		if(value.x <= arr->data[idx_m].x && value.x > arr->data[idx_m-1].x) {
			ins_idx = idx_m;
		}

		if(value.x > arr->data[idx_m].x) idx0 = idx_m;
		else idx1 = idx_m;
	}

	if(value.x != arr->data[ins_idx].x) return ins_idx;

	// y values are not binary search as last value of x = value.x is unknown
	while(ins_idx < arr->count) {
		if(arr->data[ins_idx].x == value.x && arr->data[ins_idx].y < value.y) {
			ins_idx++;
		} else break;
	}

	return ins_idx;
}

int data_array3_idx_from_binary_search(DataArray3 *arr, Vector3 value) {
	if(!arr->data || arr->count == 0) return 0;
	if(value.x < arr->data[0].x) return 0;
	if(value.x > arr->data[arr->count - 1].x) return (int) arr->count;

	int ins_idx = -1;
	if(value.x == arr->data[0].x) ins_idx = 0;

	int idx0 = 0, idx1 = (int) arr->count - 1;

	while(ins_idx < 0) {
		// + 1 to ceil and not floor if necessary (first idx already checked, last index not)
		int idx_m = (idx0 + idx1 + 1)/2;
		if(value.x <= arr->data[idx_m].x && value.x > arr->data[idx_m-1].x) {
			ins_idx = idx_m;
		}

		if(value.x > arr->data[idx_m].x) idx0 = idx_m;
		else idx1 = idx_m;
	}

	if(value.x != arr->data[ins_idx].x) return ins_idx;

	// y values are not binary search as last value of x = value.x is unknown
	while(ins_idx < arr->count) {
		if(arr->data[ins_idx].x == value.x && arr->data[ins_idx].y < value.y) {
			ins_idx++;
		} else break;
	}

	if(value.y != arr->data[ins_idx].y) return ins_idx;

	// z values are not binary search as last value of x = value.x && y = value.y is unknown
	while(ins_idx < arr->count) {
		if(arr->data[ins_idx].x == value.x && arr->data[ins_idx].y == value.y && arr->data[ins_idx].z < value.z) {
			ins_idx++;
		} else break;
	}

	return ins_idx;
}

void data_array1_insert_new(DataArray1 *arr, double value) {
	check_data_array1_add_capacity(arr);

	int insert_index = data_array1_idx_from_binary_search(arr, value);

	if (insert_index < arr->count) {
		memmove(&arr->data[insert_index + 1],
				&arr->data[insert_index],
				(arr->count - insert_index) * sizeof(double));
	}

	arr->data[insert_index] = value;
	arr->count++;
}

void data_array2_insert_new(DataArray2 *arr, Vector2 value) {
	check_data_array2_add_capacity(arr);

	int insert_index = data_array2_idx_from_binary_search(arr, value);
	
	if (insert_index < arr->count) {
		memmove(&arr->data[insert_index + 1],
				&arr->data[insert_index],
				(arr->count - insert_index) * sizeof(Vector2));
	}
	
	arr->data[insert_index] = value;
	arr->count++;
}

void data_array3_insert_new(DataArray3 *arr, Vector3 value) {
	check_data_array3_add_capacity(arr);

	int insert_index = data_array3_idx_from_binary_search(arr, value);

	if (insert_index < arr->count) {
		memmove(&arr->data[insert_index + 1],
				&arr->data[insert_index],
				(arr->count - insert_index) * sizeof(Vector3));
	}

	arr->data[insert_index] = value;
	arr->count++;
}

void data_array1_remove_at_idx(DataArray1 *arr, int idx) {
	if(!arr || idx < 0 || idx >= arr->count) return;
	memmove(arr->data+idx, arr->data+idx+1, (arr->count-idx-1) * sizeof(double));
	arr->count--;
}

void data_array2_remove_at_idx(DataArray2 *arr, int idx) {
	if(!arr || idx < 0 || idx >= arr->count) return;
	memmove(arr->data+idx, arr->data+idx+1, (arr->count-idx-1) * sizeof(Vector2));
	arr->count--;
}

void data_array3_remove_at_idx(DataArray3 *arr, int idx) {
	if(!arr || idx < 0 || idx >= arr->count) return;
	memmove(arr->data+idx, arr->data+idx+1, (arr->count-idx-1) * sizeof(Vector3));
	arr->count--;
}

bool data_array1_remove_by_value(DataArray1 *arr, double val) {
	int rm_idx = data_array1_idx_from_binary_search(arr, val);
	if(rm_idx >= arr->count) return false;
	if(arr->data[rm_idx] == val) {
		data_array1_remove_at_idx(arr, rm_idx);
		return true;
	}
	return false;
}

bool data_array2_remove_by_value(DataArray2 *arr, Vector2 val) {
	int rm_idx = data_array2_idx_from_binary_search(arr, val);
	if(rm_idx >= arr->count) return false;
	if(arr->data[rm_idx].x == val.x && arr->data[rm_idx].y == val.y) {
		data_array2_remove_at_idx(arr, rm_idx);
		return true;
	}
	return false;
}

bool data_array3_remove_by_value(DataArray3 *arr, Vector3 val) {
	for(int i = 0; i < arr->count; i++) {
		if(arr->data[i].x == val.x && arr->data[i].y == val.y && arr->data[i].z == val.z) {
			data_array3_remove_at_idx(arr, i);
			return true;
		}
	}
	return false;
}

double data_array1_get_max(DataArray1 *arr) {
	if(!arr || arr->count == 0) return NAN;
	double max = arr->data[0];
	for(int i = 1; i < arr->count; i++) {
		if(max < arr->data[i]) max = arr->data[i];
	}
	return max;
}

double data_array1_get_min(DataArray1 *arr) {
	if(!arr || arr->count == 0) return NAN;
	double min = arr->data[0];
	for(int i = 1; i < arr->count; i++) {
		if(min > arr->data[i]) min = arr->data[i];
	}
	return min;
}

Vector2 data_array2_get_max(DataArray2 *arr) {
	if(!arr || arr->count == 0) return vec2(NAN, NAN);
	Vector2 max = arr->data[0];
	for(int i = 1; i < arr->count; i++) {
		if(max.x < arr->data[i].x) max.x = arr->data[i].x;
		if(max.y < arr->data[i].y) max.y = arr->data[i].y;
	}
	return max;
}

Vector2 data_array2_get_min(DataArray2 *arr) {
	if(!arr || arr->count == 0) return vec2(NAN, NAN);
	Vector2 min = arr->data[0];
	for(int i = 1; i < arr->count; i++) {
		if(min.x > arr->data[i].x) min.x = arr->data[i].x;
		if(min.y > arr->data[i].y) min.y = arr->data[i].y;
	}
	return min;
}

Vector3 data_array3_get_max(DataArray3 *arr) {
	if(!arr || arr->count == 0) return vec3(NAN, NAN, NAN);
	Vector3 max = arr->data[0];
	for(int i = 1; i < arr->count; i++) {
		if(max.x < arr->data[i].x) max.x = arr->data[i].x;
		if(max.y < arr->data[i].y) max.y = arr->data[i].y;
		if(max.z < arr->data[i].z) max.z = arr->data[i].z;
	}
	return max;
}

Vector3 data_array3_get_min(DataArray3 *arr) {
	if(!arr || arr->count == 0) return vec3(NAN, NAN, NAN);
	Vector3 min = arr->data[0];
	for(int i = 1; i < arr->count; i++) {
		if(min.x > arr->data[i].x) min.x = arr->data[i].x;
		if(min.y > arr->data[i].y) min.y = arr->data[i].y;
		if(min.z > arr->data[i].z) min.z = arr->data[i].z;
	}
	return min;
}

void print_data_array1(DataArray1 *arr, const char *x_name) {
	printf("%s = [", x_name);
	for(int j = 0; j < arr->count; j++) {
		if(j!=0) printf(", ");
		printf("%g", arr->data[j]);
	}
	printf("]\n");
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

void print_data_array1_boxplot(DataArray1 *arr) {
	double min = arr->data[0];
	double q1 = arr->data[arr->count/4];
	double med = arr->data[arr->count/2];
	double q3 = arr->data[arr->count/4*3];
	double max = arr->data[arr->count-1];

	double sum = 0;
	for(int i = 0; i < arr->count; i++) sum += arr->data[i];
	double avg = sum / (double) arr->count;

	printf("Min: %f | Q1: %f | Median: %f | Q3: %f | Max: %f   (Avg: %f)\n",
		min, q1, med, q3, max, avg);
}

