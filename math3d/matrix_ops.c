#include "math3d.h"

// 1. Identity Matrix - Birim matris (transformasyon yok)
t_matrix4	matrix4_identity(void)
{
	t_matrix4	result;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				result.m[i][j] = 1.0f; // köşegen 1
			else
				result.m[i][j] = 0.0f; // diğer yerler 0
			j++;
		}
		i++;
	}
	return (result);
}
// 2. Matrix Multiplication - İki matris çarpımı
t_matrix4	matrix4_multiply(t_matrix4 a, t_matrix4 b)
{
	t_matrix4	result;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = 0.0f;
			k = 0;
			while (k < 4)
			{
				result.m[i][j] += a.m[i][k] * b.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}
// 3. Transform Vector - Matris ile vektör çarpımı
t_3D_vec	matrix4_transform_vec3(t_matrix4 m, t_3D_vec v)
{
	t_3D_vec	result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
	return (result);
}
// 4. Rotation X - X ekseni etrafında döndürme
t_matrix4	matrix4_rotation_x(float angle)
{
	t_matrix4	result;
	float		cos_a;
	float		sin_a;

	result = matrix4_identity();
	cos_a = cosf(angle);
	sin_a = sinf(angle);
	result.m[1][1] = cos_a;
	result.m[1][2] = -sin_a;
	result.m[2][1] = sin_a;
	result.m[2][2] = cos_a;
	return (result);
}

// 5. Rotation Y - Y ekseni etrafında döndürme
t_matrix4	matrix4_rotation_y(float angle)
{
	t_matrix4	result;
	float		cos_a;
	float		sin_a;

	result = matrix4_identity();
	cos_a = cosf(angle);
	sin_a = sinf(angle);
	result.m[0][0] = cos_a;
	result.m[0][2] = sin_a;
	result.m[2][0] = -sin_a;
	result.m[2][2] = cos_a;
	return (result);
}
