/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_projection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:53:58 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "math3d.h"
#include "render.h"
#include <math.h>

t_point2d	project_point_multi(t_point point, t_render *render)
{
	if (render->projection_type == PROJ_ISOMETRIC)
		return (project_isometric(point, render));
	else if (render->projection_type == PROJ_PERSPECTIVE)
		return (project_perspective(point, render));
	else if (render->projection_type == PROJ_ORTHOGRAPHIC)
		return (project_orthographic(point, render));
	else if (render->projection_type == PROJ_TOP_DOWN)
		return (project_top_down(point, render));
	else if (render->projection_type == PROJ_FRONT_VIEW)
		return (project_front_view(point, render));
	else if (render->projection_type == PROJ_SIDE_VIEW)
		return (project_side_view(point, render));
	else
		return (project_isometric(point, render));
}

t_point2d	project_isometric(t_point point, t_render *render)
{
	return (project_point_interactive(point, render));
}

t_point2d	project_perspective(t_point point, t_render *render)
{
	t_perspective_data	data;

	data.rotation_matrix = matrix4_rotation_y(render->rotation_y);
	data.rotation_matrix = matrix4_multiply(data.rotation_matrix,
			matrix4_rotation_x(render->rotation_x));
	data.original.x = point.x;
	data.original.y = point.y;
	data.original.z = point.z;
	data.rotated_point = matrix4_transform_vec3(data.rotation_matrix,
			data.original);
	data.scale = calculate_scale(render->map) * render->zoom_factor;
	data.z_depth = data.rotated_point.z + render->perspective_distance;
	if (data.z_depth < 1.0)
		data.z_depth = 1.0;
	data.perspective_factor = render->perspective_distance / data.z_depth;
	data.projected.x = (int)(data.rotated_point.x * data.scale
			* data.perspective_factor) + WINDOW_WIDTH / 2 + render->offset_x;
	data.projected.y = (int)(data.rotated_point.y * data.scale
			* data.perspective_factor) + WINDOW_HEIGHT / 2 + render->offset_y;
	if (point.color == -1)
		data.projected.color = COLOR_WHITE;
	else
		data.projected.color = point.color;
	return (data.projected);
}

t_point2d	project_orthographic(t_point point, t_render *render)
{
	t_orthographic_data	data;

	data.rotation_matrix = matrix4_rotation_y(render->rotation_y);
	data.rotation_matrix = matrix4_multiply(data.rotation_matrix,
			matrix4_rotation_x(render->rotation_x));
	data.original.x = point.x;
	data.original.y = point.y;
	data.original.z = point.z;
	data.rotated_point = matrix4_transform_vec3(data.rotation_matrix,
			data.original);
	data.scale = calculate_scale(render->map) * render->zoom_factor;
	data.projected.x = (int)(data.rotated_point.x * data.scale)
		+ WINDOW_WIDTH / 2 + render->offset_x;
	data.projected.y = (int)(data.rotated_point.y * data.scale)
		+ WINDOW_HEIGHT / 2 + render->offset_y;
	if (point.color == -1)
		data.projected.color = COLOR_WHITE;
	else
		data.projected.color = point.color;
	return (data.projected);
}
