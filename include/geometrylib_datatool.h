#ifndef GEOMETRYLIB_GEOMETRYLIB_DATATOOL_H
#define GEOMETRYLIB_GEOMETRYLIB_DATATOOL_H

#include "geometrylib_vec.h"
#include <stdlib.h>
#include <stdbool.h>

/*
 * ------------------------------------
 * Structures
 * ------------------------------------
 */

/**
 * @brief 1-dimensional array of doubles
 */
typedef struct DataArray1 DataArray1;

/**
 * @brief 2-dimensional Array of Vector2 (x, y)
 */
typedef struct DataArray2 DataArray2;

/**
 * @brief 3-dimensional array of Vector3 (x, y, z)
 */
typedef struct DataArray3 DataArray3;

/**
 * @brief N-dimensional array of double arrays
 */
typedef struct DataArrayN DataArrayN;


/*
 * ------------------------------------
 * Creation
 * ------------------------------------
 */

/**
 * @brief Creates a new 1-dimensional array of doubles
 *
 * @return Pointer to the newly allocated 1-dimensional array
 */
DataArray1 * data_array1_create();

/**
 * @brief Creates a new 2-dimensional array of Vector2 (x, y)
 *
 * @return Pointer to the newly allocated 2-dimensional array
 */
DataArray2 * data_array2_create();

/**
 * @brief Creates a new 3-dimensional array of Vector3 (x, y, z)
 *
 * @return Pointer to the newly allocated 3-dimensional array
 */
DataArray3 * data_array3_create();

/**
 * @brief Creates a new N-dimensional array of double arrays
 *
 * @param dimensions The number of dimensions for the array
 * @return Pointer to the newly allocated N-dimensional array
 */
DataArrayN * data_arrayn_create(int dimensions);


/*
 * ------------------------------------
 * Clearing
 * ------------------------------------
 */

/**
 * @brief Clears the contents of a 1-dimensional array
 *
 * @param arr Pointer to the 1-dimensional array to clear
 */
void data_array1_clear(DataArray1 *arr);

/**
 * @brief Clears the contents of a 2-dimensional array
 *
 * @param arr Pointer to the 2-dimensional array to clear
 */
void data_array2_clear(DataArray2 *arr);

/**
 * @brief Clears the contents of a 3-dimensional array
 *
 * @param arr Pointer to the 3-dimensional array to clear
 */
void data_array3_clear(DataArray3 *arr);

/**
 * @brief Clears the contents of an n-dimensional array
 *
 * @param arr Pointer to the n-dimensional array to clear
 */
void data_arrayn_clear(DataArrayN *arr);

/*
 * ------------------------------------
 * Destroying
 * ------------------------------------
 */

/**
 * @brief Frees all memory associated with a 1-dimensional array and destroys the array.
 *
 * @param arr Pointer to the 1-dimensional array to free
 */
void data_array1_free(DataArray1 *arr);

/**
 * @brief Frees all memory associated with a 2-dimensional array and destroys the array.
 *
 * @param arr Pointer to the 2-dimensional array to free
 */
void data_array2_free(DataArray2 *arr);

/**
 * @brief Frees all memory associated with a 3-dimensional array and destroys the array.
 *
 * @param arr Pointer to the 3-dimensional array to free
 */
void data_array3_free(DataArray3 *arr);

/**
 * @brief Frees all memory associated with an N-dimensional array and destroys the array.
 *
 * @param arr Pointer to the N-dimensional array to free
 */
void data_arrayn_free(DataArrayN *arr);

/*
 * ------------------------------------
 * Get Size
 * ------------------------------------
 */

/**
 * @brief Returns the number of elements in a 1-dimensional array
 *
 * @param arr Pointer to the 1-dimensional array
 * @return Number of elements
 */
size_t data_array1_size(DataArray1 *arr);

/**
 * @brief Returns the number of elements in a 2-dimensional array
 *
 * @param arr Pointer to the 2-dimensional array
 * @return Number of elements
 */
size_t data_array2_size(DataArray2 *arr);

/**
 * @brief Returns the number of elements in a 3-dimensional array
 *
 * @param arr Pointer to the 3-dimensional array
 * @return Number of elements
 */
size_t data_array3_size(DataArray3 *arr);

/**
 * @brief Returns the number of elements in an N-dimensional array
 *
 * @param arr Pointer to the N-dimensional array
 * @return Number of elements
 */
size_t data_arrayn_size(DataArrayN *arr);

/**
 * @brief Returns the number of dimensions in an N-dimensional array
 *
 * @param arr Pointer to the N-dimensional array
 * @return Number of dimensions
 */
size_t data_arrayn_num_dimensions(DataArrayN *arr);

/*
 * ------------------------------------
 * Get Data
 * ------------------------------------
 */

/**
 * @brief Returns a pointer to the underlying data of a 1-dimensional array
 *
 * @param arr Pointer to the 1-dimensional array
 * @return Pointer to array of doubles
 */
double * data_array1_get_data(DataArray1 *arr);

/**
 * @brief Returns a pointer to the underlying data of a 2-dimensional array
 *
 * @param arr Pointer to the 2-dimensional array
 * @return Pointer to array of Vector2
 */
Vector2 * data_array2_get_data(DataArray2 *arr);

/**
 * @brief Returns a pointer to the underlying data of a 3-dimensional array
 *
 * @param arr Pointer to the 3-dimensional array
 * @return Pointer to array of Vector3
 */
Vector3 * data_array3_get_data(DataArray3 *arr);

/**
 * @brief Returns a pointer to the underlying data of an N-dimensional array
 *
 * @param arr Pointer to the N-dimensional array
 * @return Pointer to array of double pointers
 */
double ** data_arrayn_get_data(DataArrayN *arr);


/*
 * ------------------------------------
 * Append Data
 * ------------------------------------
 */

/**
 * @brief Appends a new value to a 1-dimensional array
 *
 * @param arr Pointer to the 1-dimensional array
 * @param value The value to append
 */
void data_array1_append_new(DataArray1 *arr, double value);

/**
 * @brief Appends a new (x, y) entry to a 2-dimensional array
 *
 * @param arr Pointer to the 2-dimensional array
 * @param x X component
 * @param y Y component
 */
void data_array2_append_new(DataArray2 *arr, double x, double y);

/**
 * @brief Appends a new (x, y, z) entry to a 3-dimensional array
 *
 * @param arr Pointer to the 3-dimensional array
 * @param x X component
 * @param y Y component
 * @param z Z component
 */
void data_array3_append_new(DataArray3 *arr, double x, double y, double z);

/**
 * @brief Appends a new entry to an N-dimensional array using value array
 *
 * @param arr Pointer to the N-dimensional array
 * @param values Array of values to append
 */
void data_arrayn_append_new_from_values(DataArrayN *arr, double *values);

/**
 * @brief Appends a new entry to an N-dimensional array using pointer array
 *
 * @param arr Pointer to the N-dimensional array
 * @param p_values Array of pointers to values to append
 */
void data_arrayn_append_new_from_pointers(DataArrayN *arr, double **p_values);

/*
 * ------------------------------------
 * Insert (Sorted)
 * ------------------------------------
 */

/**
 * @brief Inserts a new (x, y) entry into a 2-dimensional array while preserving sorted order
 *
 * Assumes the x-values in the array are sorted in ascending order and inserts
 * the new (x, y) pair at the correct position to maintain that order.
 *
 * @param arr Pointer to the 2-dimensional array
 * @param x X component of the new entry
 * @param y Y component of the new entry
 */
void data_array2_insert_new(DataArray2 *arr, double x, double y);

 
 /*
 * ------------------------------------
 * Print Arrays
 * ------------------------------------
 */

/**
 * @brief Prints a 2-dimensional array with named components
 *
 * @param arr Pointer to the 2-dimensional array
 * @param x_name Name to display for the X component
 * @param y_name Name to display for the Y component
 */
void print_data_array2(DataArray2 *arr, const char *x_name, const char *y_name);

/**
 * @brief Prints a 3-dimensional array with named components
 *
 * @param arr Pointer to the 3-dimensional array
 * @param x_name Name to display for the X component
 * @param y_name Name to display for the Y component
 * @param z_name Name to display for the Z component
 */
void print_data_array3(DataArray3 *arr, const char *x_name, const char *y_name, const char *z_name);

/**
 * @brief Prints an N-dimensional array with named components
 *
 * @param arr Pointer to the N-dimensional array
 * @param name Array of names for each component
 */
void print_data_arrayN(DataArrayN *arr, const char **name);


/*
 * ------------------------------------
 * Root Finder
 * ------------------------------------
 */

/**
 * @brief Returns the next x-value to evaluate during root-finding of a monotonic function
 *
 * Uses the 2-dimensional array representing the monotonic function to compute
 * the next x position to consider.
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @return Next x-value to evaluate
 */
double root_finder_monot_func_next_x(DataArray2 *arr);

/**
 * @brief Returns the next x-value to evaluate during root-finding of a function with monotonic derivative
 *
 * The function is assumed to have a monotonic derivative (e.g., parabolic shape).
 * The minimum of the function may be below zero.
 * The root-finding process searches for roots on either side of the minimum:
 * - branch = 0: search left of the minimum
 * - branch = 1: search right of the minimum
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @param branch Which root branch to consider (0 = left, 1 = right)
 * @return Next x-value to evaluate
 */
double root_finder_monot_deriv_next_x(DataArray2 *arr, int branch);

/**
 * @brief Checks if a function with monotonic derivative represented by the array can still be negative
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @return Non-zero if the function can be negative, zero otherwise
 */
int can_be_negative_monot_deriv(DataArray2 *arr);

#endif //GEOMETRYLIB_GEOMETRYLIB_DATATOOL_H
