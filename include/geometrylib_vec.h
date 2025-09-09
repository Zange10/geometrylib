#ifndef GEOMETRYLIB_GEOMETRYLIB_VEC_H
#define GEOMETRYLIB_GEOMETRYLIB_VEC_H



/*
 * ------------------------------------
 * 2-Dimensional Vector
 * ------------------------------------
 */


/**
 * @brief Represents a 2D vector with x and y components
 */
typedef struct Vector2 {
	double x; /**< X component of the 2D vector */
	double y; /**< Y component of the 2D vector */
} Vector2;


/**
 * @brief Prints 2D-vector components and magnitude
 *
 * @param v The vector to be printed
 */
void print_vec2(Vector2 v);

/**
 * @brief Creates a 2D-vector with given x and y components
 *
 * @param x component of the vector
 * @param y component of the vector
 * @return A struct Vector2 initialized with the given components
 */
Vector2 vec2(double x, double y);


/**
 * @brief Adds two 2D vectors and returns the result
 *
 * @param v1 The first vector
 * @param v2 The second vector
 * @return A 2D Vector where each component of the vectors was added together
 */
Vector2 add_vec2(Vector2 v1, Vector2 v2);


/**
 * @brief Subtracts vector v2 from v1 (v1-v2)
 *
 * @param v1 The first vector
 * @param v2 The second vector
 * @return The resulting vector
 */
Vector2 subtract_vec2(Vector2 v1, Vector2 v2);


/**
 * @brief Multiplies a 2D-vector by a scalar
 *
 * @param v The 2D-vector that is to be multiplied
 * @param scalar The amount by which the vector is to be multiplied by
 * @return The scaled 2D-vector
 */
Vector2 scale_vec2(Vector2 v, double scalar);


/**
 * @brief Returns the squared magnitude of a given 2D-vector
 *
 * @param v The 2D-vector with respective magnitude
 * @return The squared magnitude of the 2D-given vector
 */
double sq_mag_vec2(Vector2 v);


/**
 * @brief Returns the magnitude of a given 2D-vector
 *
 * @param v The 2D-vector with respective magnitude
 * @return The magnitude of the 2D-given vector
 */
double mag_vec2(Vector2 v);


/**
 * @brief Normalizes a given 2D-vector
 *
 * @param v The 2D-vector that is to be normalized
 * @return The normalized form of the given 2D-vector
 */
Vector2 norm_vec2(Vector2 v);


/**
 * @brief Calculates the dot product of two 2D-vectors
 *
 * @param v1 Vector 1 (2D-vector)
 * @param v2 Vector 2 (2D-vector)
 * @return The resulting dot product (v1 ⋅ v2)
 */
double dot_vec2(Vector2 v1, Vector2 v2);


/**
 * @brief Calculates the angle between two 2D-vectors
 *
 * @param v1 Vector 1 (2D-vector)
 * @param v2 Vector 2 (2D-vector)
 * @return The angle between the two 2D-vectors (unsigned)
 */
double angle_vec2_vec2(Vector2 v1, Vector2 v2);


/**
 * @brief Calculates the angle between two 2D-vectors in counterclock-wise direction (-pi < angle < pi)
 *
 * @param v1 Vector 1 (2D-vector)
 * @param v2 Vector 2 (2D-vector)
 * @return The angle between the two 2D-vectors (signed)
 */
double angle_ccw_vec2_vec2(Vector2 v1, Vector2 v2);


/**
 * @brief Rotates 2D-vector in clock-wise direction
 *
 * @param v The 2D-vector that is to be rotated
 * @param gamma The angle by which the vector is to be rotated
 * @return The rotated 2D-vector
 */
Vector2 rotate_vec2(Vector2 v, double angle);


/**
 * @brief Calculates the determinant of two 2D-vectors
 *
 * @param v1 vector 1
 * @param v2 vector 2
 * @return The determinant of v1 and v2
 */
double determinant2(Vector2 v1, Vector2 v2);


/**
 * @brief Calculates the projection of v1 onto v2
 *
 * @param v1 vector 1
 * @param v2 vector 2
 * @return The projection of v1 onto v2
 */
Vector2 proj_vec2_vec2(Vector2 v1, Vector2 v2);





/*
 * ------------------------------------
 * 3-Dimensional Vector
 * ------------------------------------
 */


/**
 * @brief Represents a 3D vector with x, y, and z components
 */
typedef struct Vector3 {
	double x; /**< X component of the vector */
	double y; /**< Y component of the vector */
	double z; /**< Z component of the vector */
} Vector3;


/**
 * @brief Prints vector components and magnitude
 *
 * @param v The vector to be printed
 */
void print_vec3(Vector3 v);


/**
 * @brief Creates a vector with given x, y, and z components
 *
 * @param x component of the vector
 * @param y component of the vector
 * @param z component of the vector
 * @return A Vector initialized with the given components
 */
Vector3 vec3(double x, double y, double z);


/**
 * @brief Creates a vector from given right ascension and declination
 *
 * @param right_ascension Right Ascension of vector
 * @param declination Declination of vector
 * @return A Vector initialized with the given components
 */
Vector3 vec3_from_angles(double right_ascension, double declination);


/**
 * @brief Adds two vectors and returns the result
 *
 * @param v1 The first vector
 * @param v2 The second vector
 * @return A struct Vector where each component of the vectors was added together
 */
Vector3 add_vec3(Vector3 v1, Vector3 v2);


/**
 * @brief Subtracts vector v2 from v1 (v1-v2)
 *
 * @param v1 The first vector
 * @param v2 The second vector
 * @return The resulting vector
 */
Vector3 subtract_vec3(Vector3 v1, Vector3 v2);


/**
 * @brief Multiplies a vector by a scalar
 *
 * @param v The vector that is to be multiplied
 * @param scalar The amount by which the vector is to be multiplied by
 * @return The scaled vector
 */
Vector3 scale_vec3(Vector3 v, double scalar);


/**
 * @brief Returns the squared magnitude of a given vector
 *
 * @param v The vector with respective magnitude
 * @return The squared magnitude of the given vector
 */
double sq_mag_vec3(Vector3 v);


/**
 * @brief Returns the magnitude of a given vector
 *
 * @param v The vector with respective magnitude
 * @return The magnitude of the given vector
 */
double mag_vec3(Vector3 v);


/**
 * @brief Normalizes a given vector
 *
 * @param v The vector that is to be normalized
 * @return The normalized form of the given vector
 */
Vector3 norm_vec3(Vector3 v);


/**
 * @brief Calculates the dot product of two vectors
 *
 * @param v1 Vector 1
 * @param v2 Vector 2
 * @return The resulting dot product v1 ⋅ v2
 */
double dot_vec3(Vector3 v1, Vector3 v2);


/**
 * @brief Calculates the cross product of two vectors
 *
 * @param v1 Vector 1
 * @param v2 Vector 2
 * @return The resulting cross product (v1 x v2)
 */
Vector3 cross_vec3(Vector3 v1, Vector3 v2);


/**
 * @brief Calculates the angle between two vectors
 *
 * @param v1 Vector 1
 * @param v2 Vector 2
 * @return The angle between the two vectors
 */
double angle_vec3_vec3(Vector3 v1, Vector3 v2);



/**
 * @brief Rotates a vector around an axis in ccw direction (right hand rule)
 *
 * @param v The vector that is to be rotated
 * @param axis The axis-vector around which the vector is to be rotated
 * @param angle The angle by which the vector is to be rotated
 * @return The rotated vector
 */
Vector3 rotate_vector_around_axis(Vector3 v, Vector3 axis, double angle);


/**
 * @brief Calculates the projection vector of vector on another vector
 *
 * @param v1 The vector to be projected
 * @param v2 The vector that v1 gets projected onto
 * @return The projection vector
 */
Vector3 proj_vec3_vec3(Vector3 v1, Vector3 v2);




#endif //GEOMETRYLIB_GEOMETRYLIB_VEC_H
