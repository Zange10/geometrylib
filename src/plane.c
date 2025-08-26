#include "../include/geometrylib_plane.h"
#include <math.h>


Plane3 constr_plane3(Vector3 loc, Vector3 u, Vector3 v) {
	Plane3 p;
	p.loc = loc;
	p.u = u;
	p.v = v;
	return p;
}

Vector3 norm_vector_plane3(Plane3 p) {
	return cross_vec3(p.u, p.v);
}

double angle_plane3_vec3(Plane3 p, Vector3 v) {
	return M_PI/2 - angle_vec3_vec3(norm_vector_plane3(p), v);
}

double angle_plane_plane(Plane3 p1, Plane3 p2) {
	return angle_vec3_vec3(norm_vector_plane3(p1), norm_vector_plane3(p2));
}

Vector3 calc_intersecting_line_dir_plane3(Plane3 p1, Plane3 p2) {
	double M[3][5] = {
			{p1.u.x, p1.v.x, -p2.u.x, -p2.v.x, p2.loc.x-p1.loc.x},
			{p1.u.y, p1.v.y, -p2.u.y, -p2.v.y, p2.loc.y-p1.loc.y},
			{p1.u.z, p1.v.z, -p2.u.z, -p2.v.z, p2.loc.z-p1.loc.z}
	};
	
	// make 0-triangle
	for(int i = 4; i >= 0; i--) M[1][i] = M[0][0]*M[1][i] - M[1][0] * M[0][i];  // I  -> II
	for(int i = 4; i >= 0; i--) M[2][i] = M[0][0]*M[2][i] - M[2][0] * M[0][i];  // I  -> III
	for(int i = 4; i >= 0; i--) M[2][i] = M[1][1]*M[2][i] - M[2][1] * M[1][i];  // II -> III
	
	double a = M[2][2];
	double b = M[2][3];
	
	// if planes are equal (inside ecliptic for p_0)
	// return p2.u because for earth ecliptic cases draw line from Sun to Earth
	if(a == 0) return scale_vec3(p2.u, 1);
	
	Vector3 dir = {
			-b/a*p2.u.x + p2.v.x,
			-b/a*p2.u.y + p2.v.y,
			-b/a*p2.u.z + p2.v.z,
	};
	
	return dir;
}

Vector3 proj_vec_plane(Vector3 v, Plane3 p) {
	Vector3 n = norm_vector_plane3(p);
	Vector3 proj_n = proj_vec3_vec3(v,n);
	return subtract_vec3(v, proj_n);
}
