#ifndef GEOMETRYLIB_GEOMETRYLIB_PLANE_H
#define GEOMETRYLIB_GEOMETRYLIB_PLANE_H

#include "geometrylib_vec.h"


/**
 * @brief Represents a plane in 3D space defined by a location vector and two directional vectors
 */
typedef struct Plane3 {
	Vector3 loc; /**< Location vector of the plane */
	Vector3 u;   /**< Directional vector 'u' */
	Vector3 v;   /**< Directional vector 'v' */
} Plane3;


/**
 * @brief Constructs a plane with a given location and two given direction vectors
 *
 * @param loc Location vector
 * @param u direction vector
 * @param v direction vector
 * @return The constructed plane
 */
Plane3 constr_plane3(Vector3 loc, Vector3 u, Vector3 v);


/**
 * @brief Calculates the normal vector of a plane
 *
 * @param p The given plane
 * @return The normal vector of the given plane
 */
Vector3 norm_vector_plane3(Plane3 p);


/**
 * @brief Calculates the angle between a plane and a vector
 *
 * @param p The plane
 * @param v The vector
 * @return The angle between the plane and the vector
 */
double angle_plane3_vec3(Plane3 p, Vector3 v);


/**
 * @brief Calculates the angle between two planes
 *
 * @param p1 Plane 1
 * @param p2 Plane 2
 * @return The angle between the two planes
 */
double angle_plane3_plane3(Plane3 p1, Plane3 p2);


/**
 * @brief Calculates the direction of the intersecting line between two planes
 *
 * @param p1 Plane 1
 * @param p2 Plane 2
 * @return The direction of the intersecting line
 */
Vector3 calc_intersecting_line_dir_plane3(Plane3 p1, Plane3 p2);


/**
 * @brief Calculates the projection vector of vector on plane
 *
 * @param v The vector
 * @param p The plane
 * @return The projection vector
 */
Vector3 proj_vec3_plane3(Vector3 v, Plane3 p);

#endif //GEOMETRYLIB_GEOMETRYLIB_PLANE_H
