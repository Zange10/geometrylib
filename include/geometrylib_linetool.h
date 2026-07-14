#ifndef KMAT_GEOMETRYLIB_LINETOOL_H
#define KMAT_GEOMETRYLIB_LINETOOL_H


#include "geometrylib_datatool.h"


/*
 * ------------------------------------
 * Interpolation
 * ------------------------------------
 */

/**
 * @brief Returns the interpolated y-value to a given x-value for a sorted 2-dimensional array
 *
 * @param data_array Pointer to the 2-dimensional array of (x, y) pairs (x is sorted)
 * @param x x-value for which the y-value is to be interpolated
 * @return Interpolated y-value
 */
double interpolate_from_sorted_data_array2(DataArray2 *data_array, double x);


/*
 * ------------------------------------
 * Intersections
 * ------------------------------------
 */

/**
 * @brief Returns all intersections between two line arrays
 *
 * @param line0 Pointer to the first 2-dimensional array of (x, y) pairs (x is sorted)
 * @param line1 Pointer to the second 2-dimensional array of (x, y) pairs (x is sorted)
 * @return Array of intersections
 */
DataArray2 * get_line_intersections(DataArray2 *line0, DataArray2 *line1);


#endif //KMAT_GEOMETRYLIB_LINETOOL_H
