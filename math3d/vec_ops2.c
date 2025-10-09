#include "math3d.h"

// 6. Vector Length - Vektör uzunluğu
float	vec3_length(t_3D_vec v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

// 7. Normalize - Birim vektöre çevir
t_3D_vec	vec3_normalize(t_3D_vec v)
{
	float		length;
	t_3D_vec	result;

	length = vec3_length(v);
	if (length == 0.0f)
	{
		result.x = 0.0f;
		result.y = 0.0f;
		result.z = 0.0f;
		return (result);
	}
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}
