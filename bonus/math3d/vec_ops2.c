/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_ops2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:52:29 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math3d.h"

float	vec3_length(t_3D_vec v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

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
