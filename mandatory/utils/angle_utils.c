/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 14:20:49 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"
#include <math.h>

float	get_projection_axes_angle_deg(void)
{
	float	dot;
	float	mag;
	float	cos_theta;
	float	angle_rad;

	dot = 1 * 1 + 1 * (-1);
	mag = sqrtf(1 * 1 + 1 * 1) * sqrtf(1 * 1 + (-1) * (-1));
	if (mag <= FLT_EPSILON)
		return (0.0f);
	cos_theta = dot / mag;
	if (cos_theta > 1.0f)
		cos_theta = 1.0f;
	else if (cos_theta < -1.0f)
		cos_theta = -1.0f;
	angle_rad = acosf(cos_theta);
	return (angle_rad * 180.0f / M_PI);
}

float	get_isometric_axes_angle_deg(void)
{
	t_angle_calc	angel_calc;

	angel_calc.angle = 30.0f * M_PI / 180.0f;
	angel_calc.x1 = cosf(angel_calc.angle);
	angel_calc.y1 = sinf(angel_calc.angle);
	angel_calc.x2 = -cosf(angel_calc.angle);
	angel_calc.y2 = sinf(angel_calc.angle);
	angel_calc.dot = angel_calc.x1 * angel_calc.x2 + angel_calc.y1
		* angel_calc.y2;
	angel_calc.mag = sqrtf(angel_calc.x1 * angel_calc.x1 + angel_calc.y1
			* angel_calc.y1) * sqrtf(angel_calc.x2 * angel_calc.x2
			+ angel_calc.y2 * angel_calc.y2);
	if (angel_calc.mag <= FLT_EPSILON)
		return (0.0f);
	angel_calc.cos_theta = angel_calc.dot / angel_calc.mag;
	if (angel_calc.cos_theta > 1.0f)
		angel_calc.cos_theta = 1.0f;
	else if (angel_calc.cos_theta < -1.0f)
		angel_calc.cos_theta = -1.0f;
	angel_calc.angle_rad = acosf(angel_calc.cos_theta);
	return (angel_calc.angle_rad * 180.0f / M_PI);
}
