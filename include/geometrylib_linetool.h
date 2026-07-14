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



#endif //KMAT_GEOMETRYLIB_LINETOOL_H
