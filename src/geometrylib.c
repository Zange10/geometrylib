#include "geometrylib.h"
#include <math.h>

double deg2rad(double deg) {
	return deg/180*M_PI;
}

double rad2deg(double rad) {
	return rad/M_PI*180;
}

double pi_norm(double rad) {
	while(rad >= 2*M_PI) rad -= 2*M_PI;
	while(rad < 0) rad += 2*M_PI;
	return rad;
}
