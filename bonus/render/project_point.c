/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:02:57 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 19:31:46 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "math3d.h"
#include "render.h"
#include <math.h>

static float	deg_to_rad(float degree)
{
	return (degree * M_PI / 180.0f);
}

t_point2d	project_point_scaled(t_point point, t_map *map)
{
	t_point2d	projected;
	float		scale;
	float		z_factor;
	float		centered_x;
	float		centered_y;

	scale = calculate_scale(map);
	z_factor = calculate_z_factor(map);
	centered_x = point.x - (map->width - 1) / 2.0f;
	centered_y = point.y - (map->height - 1) / 2.0f;
	projected.x = (centered_x - centered_y) * cos(deg_to_rad(30.0f)) * scale
		+ WINDOW_WIDTH / 2;
	projected.y = (centered_x + centered_y - point.z * z_factor)
		* sin(deg_to_rad(30.0f)) * scale + WINDOW_HEIGHT / 2;
	return (projected);
}

t_point2d	project_point_interactive(t_point point, t_render *render)
{
	t_point2d			projected;
	t_projection_vars	proj_vars;

	proj_vars.scale = calculate_scale(render->map) * render->zoom_factor;
	proj_vars.z_factor = calculate_z_factor(render->map);
	proj_vars.centered_x = point.x - (render->map->width - 1) / 2.0f;
	proj_vars.centered_y = point.y - (render->map->height - 1) / 2.0f;
	proj_vars.rotated_x = proj_vars.centered_x * cos(render->rotation_y)
		- proj_vars.centered_y * sin(render->rotation_y);
	proj_vars.rotated_y = proj_vars.centered_x * sin(render->rotation_y)
		+ proj_vars.centered_y * cos(render->rotation_y);
	projected.x = ((proj_vars.rotated_x + proj_vars.rotated_y)
			* cos(deg_to_rad(30.0f)) * proj_vars.scale + WINDOW_WIDTH / 2
			+ render->offset_x);
	projected.y = (proj_vars.rotated_y - proj_vars.rotated_x - point.z
			* proj_vars.z_factor) * sin(deg_to_rad(30.0f)) * proj_vars.scale
		+ WINDOW_HEIGHT / 2 + render->offset_y;
	projected.color = set_point_color(point.color);
	return (projected);
}

t_point2d	project_point(t_point point)
{
	t_point2d	projected;
	float		scale;

	scale = 20.0;
	projected.x = (point.x - point.y) * scale + WINDOW_WIDTH / 2;
	projected.y = (point.x + point.y - point.z * 0.3) * scale * 0.5
		+ WINDOW_HEIGHT / 3;
	projected.color = set_point_color(point.color);
	return (projected);
}
