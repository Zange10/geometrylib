#include <math.h>

#include "geometrylib_linetool.h"
#include "data_array_def.h"

double interpolate_from_sorted_data_array2(DataArray2 *data_array, double x) {
	Vector2 *data = data_array2_get_data(data_array);
	size_t num_data = data_array2_size(data_array);
	if(x < data[0].x || x > data[num_data-1].x) return NAN;

	int idx0 = 0, idx1 = (int) data_array->count-1;
	while(idx1-idx0 > 1) {
		int idx_m = (idx0 + idx1)/2;
		if(data_array->data[idx_m].x < x == data_array->data[idx0].y < x) idx0 = idx_m;
		else idx1 = idx_m;
	}

	Vector2 p0 = data[idx0], p1 = data[idx1];

	double m = (p1.y-p0.y) / (p1.x-p0.x);
	return (x-p0.x) * m + p0.y;
}
