#include "math3d.h"

t_matrix4	matrix4_translation(float x, float y, float z)
{
	t_matrix4	result;

	result = matrix4_identity();
	result.m[0][3] = x;
	result.m[1][3] = y;
	result.m[2][3] = z;
	return (result);
}
