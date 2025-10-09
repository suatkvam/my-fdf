#include "math3d.h"

// 1. Vector Addition - İki vektörü topla
t_3D_vec	vec3_add(t_3D_vec a, t_3D_vec b)
{
	t_3D_vec	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

// 2. Vector Subtraction - İki vektörü çıkar
t_3D_vec	vec3_sub(t_3D_vec a, t_3D_vec b)
{
	t_3D_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}
// 3. Scalar Multiplication - Vektörü sayı ile çarp
t_3D_vec	vec3_mul(t_3D_vec v, float scalar)
{
	t_3D_vec	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

// 4. Dot Product - İç çarpım (projeksiyon için)
float	vec3_dot(t_3D_vec a, t_3D_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// 5. Cross Product - Dış çarpım (normal vector için)
t_3D_vec	vec3_cross(t_3D_vec a, t_3D_vec b)
{
	t_3D_vec result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
