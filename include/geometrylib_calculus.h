#ifndef KMAT_GEOMETRYLIB_CALCULUS_H
#define KMAT_GEOMETRYLIB_CALCULUS_H

#include "geometrylib_datatool.h"


/*
 * ------------------------------------
 * Inter-/Extrapolation
 * ------------------------------------
 */

/**
 * @brief Interpolates/Extrapolates y-value from given line and x-value
 *
 * @param p0 Point on line
 * @param p1 Point on line
 * @param x x-value to get the y-value for
 * @return Inter-/Extrapolated y-value
 */
double get_y_value_from_x_value_of_line(Vector2 p0, Vector2 p1, double x);

/**
 * @brief Interpolates/Extrapolates x-value from given line and y-value
 *
 * @param p0 Point on line
 * @param p1 Point on line
 * @param y y-value to get the x-value for
 * @return Inter-/Extrapolated x-value
 */
double get_x_value_from_y_value_of_line(Vector2 p0, Vector2 p1, double y);

/**
 * @brief Finds the root in a 2-dimensional data array that has one root
 *
 * @param arr Pointer to the 2-dimensional array
 * @return Determined root
 */
double get_single_root_of_line_array(DataArray2 *arr);

/**
 * @brief Finds the shifted root (shifted by given y) in a 2-dimensional data array that has one root
 *
 * @param arr Pointer to the 2-dimensional array
 * @param y Amount of y to shift the array's y
 * @return Determined root
 */
double get_single_shifted_root_of_line_array(DataArray2 *arr, double y);


/*
 * ------------------------------------
 * Difference and Gradient
 * ------------------------------------
 */

/**
 * @brief Computes the difference between consecutive elements in a 1-dimensional array
 *
 * The resulting array will have one fewer element than the input array.
 * Each element is calculated as arr[i+1] - arr[i].
 *
 * @param arr Pointer to the 1-dimensional array
 * @return A newly allocated DataArray1 containing the differences,
 *         or NULL if the input array is NULL
 */
DataArray1 * data_array1_get_diff(DataArray1 *arr);

/**
 * @brief Computes the gradient between consecutive elements in a 2-dimensional array
 *
 * For each consecutive pair of elements, the x component of the gradient is
 * the midpoint of the x values, and the y component is the slope (Δy / Δx).
 * The resulting array will have one fewer element than the input array.
 *
 * @param arr Pointer to the 2-dimensional array
 * @return A newly allocated DataArray2 containing the gradients,
 *         or NULL if the input array is NULL
 */
DataArray2 * data_array2_get_gradient(DataArray2 *arr);



/*
 * ------------------------------------
 * Extreme values
 * ------------------------------------
 */

/**
 * @brief Returns the index of the minimum of a function with a single local minimum
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @return Index of minimum
 */
int get_idx_of_unimodal_func_minimum(DataArray2 *arr);

/**
 * @brief Returns the index of the maximum of a function with a single local maximum
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @return Index of maximum
 */
int get_idx_of_unimodal_func_maximum(DataArray2 *arr);

/**
 * @brief Returns the index of the entry that has an x smaller than the given one with the next entry being bigger
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @param x Requested x
 * @return Index of x index (floored)
 */
int get_idx_of_func_x(DataArray2 *arr, double x);

/**
 * @brief Returns the next x-value to evaluate during minimum-finding of a unimodal function with a single minimum
 *
 * Returns NAN if the distance between the points to search for becomes too small
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @param min_idx Index of the minimum of arr - Gets calculated if no valid is given
 * @param min_diff_ratio The minimum distance to the next point as a ratio of the difference in x between points
 * @param min_dx The minimum distance to the next point
 * @return Next x-value to evaluate (NAN if no next value to evaluate)
 */
double get_next_x_for_min_search(DataArray2 *arr, int min_idx, double min_diff_ratio, double min_dx);

/**
 * @brief Returns the next x-value to evaluate during maximum-finding of a unimodal function with a single maximum
 *
 * Returns NAN if the distance between the points to search for becomes too small
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @param max_idx Index of the minimum of arr - Gets calculated if no valid is given
 * @param min_diff_ratio The minimum distance to the next point as a ratio of the difference in x between points
 * @param min_dx The minimum distance to the next point
 * @return Next x-value to evaluate (NAN if no next value to evaluate)
 */
double get_next_x_for_max_search(DataArray2 *arr, int max_idx, double min_diff_ratio, double min_dx);

/**
 * @brief Returns the minimum y-value at the x of the current minimum wrt the surrounding points
 *
 * Extends the previous lines to the current minimum and returns the minimum value from that.
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @param min_idx Index of the minimum of arr - Gets calculated if no valid is given
 * @param num_point_range Number of points/lines to consider before and after minimum
 * @return Minimum y-value from the analyzed lines - Returns NAN if point range extends over array
 */
double min_achievable_value_from_prev_and_next_points(DataArray2 *arr, int min_idx, int num_point_range);

/**
 * @brief Returns the maximum y-value at the x of the current maximum wrt the surrounding points
 *
 * Extends the previous lines to the current maximum and returns the maximum value from that.
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @param max_idx Index of the minimum of arr - Gets calculated if no valid is given
 * @param num_point_range Number of points/lines to consider before and after minimum
 * @return Maximum y-value from the analyzed lines - Returns NAN if point range extends over array
 */
double max_achievable_value_from_prev_and_next_points(DataArray2 *arr, int max_idx, int num_point_range);


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
 * @param min_diff_ratio The minimum distance to the next point as a ratio of the difference in x between points
 * @param min_dx The minimum distance to the next point
 * @return Next x-value to evaluate
 */
double root_finder_monot_func_next_x(DataArray2 *arr, double min_diff_ratio, double min_dx);

/**
 * @brief Returns the next x-value to evaluate during root-finding of a function with monotonic derivative
 *
 * The function is assumed to have a monotonic derivative (e.g., parabolic shape).
 * The minimum of the function may be below zero.
 * The root-finding process searches for roots on either side of the minimum:
 * - branch = false: search left of the minimum
 * - branch = true: search right of the minimum
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @param right_branch Which root branch to consider (0 = left, 1 = right)
 * @return Next x-value to evaluate
 */
double root_finder_monot_deriv_next_x(DataArray2 *arr, bool right_branch);

/**
 * @brief Returns the next x-value to evaluate during root-finding of a unimodal function with a single minimum
 *
 * Returns NAN if the distance between the points to search for becomes too small
 * or if function can presumably not become 0
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @param min_diff_ratio The minimum distance to the next point as a ratio of the difference in x between points
 * @param min_dx The minimum distance to the next point
 * @param left_branch Which root branch to consider (true = left, false = right)
 * @return Next x-value to evaluate (NAN if no next value to evaluate)
 */
double root_finder_single_minimum_func_next_x(DataArray2 *arr, bool left_branch, double min_diff_ratio, double min_dx);

/**
 * @brief Checks if a function with monotonic derivative represented by the array can still be negative
 *
 * @param arr Pointer to the 2-dimensional array of (x, y) pairs
 * @return Non-zero if the function can be negative, zero otherwise
 */
int can_be_negative_monot_deriv(DataArray2 *arr);

#endif //KMAT_GEOMETRYLIB_CALCULUS_H
