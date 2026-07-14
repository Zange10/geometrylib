#ifndef KMAT_DATA_ARRAY_DEF_H
#define KMAT_DATA_ARRAY_DEF_H

#include "geometrylib_vec.h"
#include <stdlib.h>
#include <stdbool.h>

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

#endif //KMAT_DATA_ARRAY_DEF_H
