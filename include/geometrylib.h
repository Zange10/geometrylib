#ifndef GEOMETRYLIB_GEOMETRYLIB_H
#define GEOMETRYLIB_GEOMETRYLIB_H





/**
 * @brief Converts degrees to radians
 *
 * @param deg Angle in degrees
 * @return Angle in radians
 */
double deg2rad(double deg);


/**
 * @brief Converts degrees to radians
 *
 * @param rad Angle in radians
 * @return Angle in degrees
 */
double rad2deg(double rad);


/**
 * @brief Normalizes angle (in radians) to values between 0 and 2π
 *
 * @param rad Value to be normalized
 * @return Normalized value (0 ≤ value ⋖ 2π)
 */
double pi_norm(double rad);

#endif // GEOMETRYLIB_GEOMETRYLIB_H
