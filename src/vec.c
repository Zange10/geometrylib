#include "../include/geometrylib_vec.h"
#include <stdio.h>
#include <math.h>


/*
 * ------------------------------------
 * 2-Dimensional Vector
 * ------------------------------------
 */

void print_vec2(Vector2 v) {
	printf("(%f, %f)\n", v.x, v.y);
}

Vector2 vec2(double x, double y) {
	Vector2 v = {x, y};
	return v;
}

Vector2 add_vec2(Vector2 v1, Vector2 v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Vector2 subtract_vec2(Vector2 v1, Vector2 v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

Vector2 scale_vec2(Vector2 v, double scalar) {
	v.x *= scalar;
	v.y *= scalar;
	return v;
}

double sq_mag_vec2(Vector2 v) {
	return v.x*v.x + v.y*v.y;
}

double mag_vec2(Vector2 v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

Vector2 norm_vec2(Vector2 v) {
	double mag = mag_vec2(v);
	return scale_vec2(v, 1 / mag);
}

double dot_vec2(Vector2 v1, Vector2 v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

double angle_vec2_vec2(Vector2 v1, Vector2 v2) {
	return fabs(acos(dot_vec2(v1,v2) / (mag_vec2(v1)*mag_vec2(v2))));
}

double angle_ccw_vec2_vec2(Vector2 v1, Vector2 v2) {
	double angle = angle_vec2_vec2(v1,v2);
	if(determinant2(v1, v2) > 0) angle *= -1;
	return angle;
}

Vector2 rotate_vec2(Vector2 v, double angle) {
	Vector2 v_rot;
	angle *= -1; // clockwise rotation
	v_rot.x = cos(angle)*v.x - sin(angle)*v.y;
	v_rot.y = sin(angle)*v.x + cos(angle)*v.y;
	return v_rot;
}

double determinant2(Vector2 v1, Vector2 v2) {
	return v1.x*v2.y - v1.y*v2.x;
}

Vector2 proj_vec2_vec2(Vector2 v1, Vector2 v2) {
	v2 = norm_vec2(v2);
	return scale_vec2(v2, dot_vec2(v1,v2));
}




/*
 * ------------------------------------
 * 3-Dimensional Vector
 * ------------------------------------
 */

void print_vec3(Vector3 v) {
	printf("(%f, %f, %f) | (%f)\n", v.x, v.y, v.z, mag_vec3(v));
}

Vector3 vec3(double x, double y, double z) {
	Vector3 v = {x, y, z};
	return v;
}

Vector3 add_vec3(Vector3 v1, Vector3 v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

Vector3 subtract_vec3(Vector3 v1, Vector3 v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

Vector3 scale_vec3(Vector3 v, double scalar) {
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return v;
}

double sq_mag_vec3(Vector3 v) {
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

double mag_vec3(Vector3 v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vector3 norm_vec3(Vector3 v) {
	double mag = mag_vec3(v);
	return scale_vec3(v, 1 / mag);
}

double dot_vec3(Vector3 v1, Vector3 v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vector3 cross_vec3(Vector3 v1, Vector3 v2) {
	Vector3 v;
	v.x = v1.y*v2.z - v1.z*v2.y;
	v.y = v1.z*v2.x - v1.x*v2.z;
	v.z = v1.x*v2.y - v1.y*v2.x;
	return v;
}

double angle_vec3_vec3(Vector3 v1, Vector3 v2) {
	double acos_part = dot_vec3(v1,v2) / (mag_vec3(v1)*mag_vec3(v2));
	// some small imprecisions can lead to acos(1.0000....01) (nan) -> rounding to 1/-1
	if(acos_part >  1) acos_part = 1;
	if(acos_part < -1) acos_part = -1;
	double angle = fabs(acos(acos_part));
	return angle;
}

Vector3 rotate_vector_around_axis(Vector3 v, Vector3 axis, double angle) {
	Vector3 u = norm_vec3(axis);
	double ca = cos(angle);
	double mca = 1-cos(angle);
	double sa = sin(angle);
	
	double R[3][3] = {
			{ca+u.x*u.x*mca,        u.x*u.y*mca-u.z*sa,         u.x*u.z*mca+u.y*sa},
			{u.y*u.x*mca+u.z*sa,    ca+u.y*u.y*mca,             u.y*u.z*mca-u.x*sa},
			{u.z*u.x*mca-u.y*sa,    u.z*u.y*mca+u.x*sa,         ca+u.z*u.z*mca}
	};
	
	double v_vec[3] = {v.x, v.y, v.z};
	double rot_v[3] = {0,0,0};
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			rot_v[i] += R[i][j]*v_vec[j];
		}
	}
	Vector3 rotated_vector = {rot_v[0], rot_v[1], rot_v[2]};
	return rotated_vector;
}

Vector3 proj_vec3_vec3(Vector3 v1, Vector3 v2) {
	v2 = norm_vec3(v2);
	return scale_vec3(v2, dot_vec3(v1,v2));
}