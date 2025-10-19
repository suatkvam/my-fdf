/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:52:22 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math3d.h"

t_3D_vec	vec3_add(t_3D_vec a, t_3D_vec b)
{
	t_3D_vec	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_3D_vec	vec3_sub(t_3D_vec a, t_3D_vec b)
{
	t_3D_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_3D_vec	vec3_mul(t_3D_vec v, float scalar)
{
	t_3D_vec	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

float	vec3_dot(t_3D_vec a, t_3D_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_3D_vec	vec3_cross(t_3D_vec a, t_3D_vec b)
{
	t_3D_vec	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
