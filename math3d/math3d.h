#ifndef MATH3D_H
# define MATH3D_H

# include <math.h>

// 3D Vector structure
typedef struct s_3D_vec
{
	float	x;
	float	y;
	float	z;
}			t_3D_vec;

// 4D Vector structure (homogeneous coordinates)
typedef struct s_4D_vec
{
	float	x;
	float	y;
	float	z;
	float	w;
}			t_4D_vec;

// 4x4 Matrix structure
typedef struct s_matrix4
{
	float	m[4][4];
}			t_matrix4;

// Vector operations
t_3D_vec	vec3_add(t_3D_vec a, t_3D_vec b);
t_3D_vec	vec3_sub(t_3D_vec a, t_3D_vec b);
t_3D_vec	vec3_mul(t_3D_vec v, float scalar);
t_3D_vec	vec3_cross(t_3D_vec a, t_3D_vec b);
float		vec3_dot(t_3D_vec a, t_3D_vec b);
float		vec3_length(t_3D_vec v);
t_3D_vec	vec3_normalize(t_3D_vec v);

// Matrix operations
t_matrix4	matrix4_identity(void);
t_matrix4	matrix4_multiply(t_matrix4 a, t_matrix4 b);
t_3D_vec	matrix4_transform_vec3(t_matrix4 m, t_3D_vec v);

// Transformation matrices
t_matrix4	matrix4_rotation_x(float angle);
t_matrix4	matrix4_rotation_y(float angle);
t_matrix4	matrix4_rotation_z(float angle);
t_matrix4	matrix4_translation(float x, float y, float z);
t_matrix4	matrix4_scale(float x, float y, float z);

#endif