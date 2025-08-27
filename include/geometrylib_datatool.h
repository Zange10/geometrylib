#ifndef GEOMETRYLIB_GEOMETRYLIB_DATATOOL_H
#define GEOMETRYLIB_GEOMETRYLIB_DATATOOL_H

#include "geometrylib_vec.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct DataArray1 DataArray1;
typedef struct DataArray2 DataArray2;
typedef struct DataArray3 DataArray3;
typedef struct DataArrayN DataArrayN;

DataArray1 * data_array1_create();
DataArray2 * data_array2_create();
DataArray3 * data_array3_create();
DataArrayN * data_arrayn_create(int dimensions);

void data_array1_free(DataArray1* arr);
void data_array2_free(DataArray2* arr);
void data_array3_free(DataArray3* arr);
void data_arrayn_free(DataArrayN* arr);

size_t data_array1_size(DataArray1 *arr);
size_t data_array2_size(DataArray2 *arr);
size_t data_array3_size(DataArray3 *arr);
size_t data_arrayn_size(DataArrayN *arr);

double  * get_data_array1(DataArray1 *arr);
Vector2 * get_data_array2(DataArray2 *arr);
Vector3 * get_data_array3(DataArray3 *arr);
double ** get_data_array4(DataArrayN *arr);

void data_array1_append_new(DataArray1 *arr, double value);
void data_array2_append_new(DataArray2 *arr, double x, double y);
void data_array3_append_new(DataArray3 *arr, double x, double y, double z);
void data_arrayn_append_new_from_values(DataArrayN *arr, double *values);
void data_arrayn_append_new_from_pointers(DataArrayN *arr, double **p_values);

void data_array2_insert_new(DataArray2 *arr, double x, double y);

double root_finder_monot_func_next_x(DataArray2 *arr);
double root_finder_monot_deriv_next_x(DataArray2 *arr, int branch);
int can_be_negative_monot_deriv(DataArray2 *arr);

#endif //GEOMETRYLIB_GEOMETRYLIB_DATATOOL_H
