/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:59:14 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 18:02:02 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH3D_H
# define MATH3D_H

# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_3D_vec
{
	float	x;
	float	y;
	float	z;
}			t_3D_vec;

typedef struct s_4D_vec
{
	float	x;
	float	y;
	float	z;
	float	w;
}			t_4D_vec;

typedef struct s_matrix4
{
	float	m[4][4];
}			t_matrix4;

t_3D_vec	vec3_add(t_3D_vec a, t_3D_vec b);
t_3D_vec	vec3_sub(t_3D_vec a, t_3D_vec b);
t_3D_vec	vec3_mul(t_3D_vec v, float scalar);
t_3D_vec	vec3_cross(t_3D_vec a, t_3D_vec b);
float		vec3_dot(t_3D_vec a, t_3D_vec b);
float		vec3_length(t_3D_vec v);
t_3D_vec	vec3_normalize(t_3D_vec v);

t_matrix4	matrix4_identity(void);
t_matrix4	matrix4_multiply(t_matrix4 a, t_matrix4 b);
t_3D_vec	matrix4_transform_vec3(t_matrix4 m, t_3D_vec v);

t_matrix4	matrix4_rotation_x(float angle);
t_matrix4	matrix4_rotation_y(float angle);
t_matrix4	matrix4_rotation_z(float angle);
t_matrix4	matrix4_translation(float x, float y, float z);
t_matrix4	matrix4_scale(float x, float y, float z);

#endif
