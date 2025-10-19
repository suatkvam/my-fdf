/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:54:04 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "render.h"

t_point2d	project_top_down(t_point point, t_render *render)
{
	t_point2d	projected;
	float		scale;
	int			intensity;

	scale = calculate_scale(render->map) * render->zoom_factor;
	projected.x = (int)(point.x * scale) + WINDOW_WIDTH / 2 + render->offset_x;
	projected.y = (int)(point.y * scale) + WINDOW_HEIGHT / 2 + render->offset_y;
	if (point.color == -1)
	{
		intensity = (int)(point.z * 20 + 128);
		if (intensity < 0)
			intensity = 0;
		if (intensity > 255)
			intensity = 255;
		projected.color = (intensity << 16) | (intensity << 8) | intensity;
	}
	else
		projected.color = point.color;
	return (projected);
}

t_point2d	project_front_view(t_point point, t_render *render)
{
	t_point2d	projected;
	float		scale;

	scale = calculate_scale(render->map) * render->zoom_factor;
	projected.x = (int)(point.x * scale) + WINDOW_WIDTH / 2 + render->offset_x;
	projected.y = (int)(-point.z * scale) + WINDOW_HEIGHT / 2
		+ render->offset_y;
	if (point.color == -1)
		projected.color = COLOR_WHITE;
	else
		projected.color = point.color;
	return (projected);
}

t_point2d	project_side_view(t_point point, t_render *render)
{
	t_point2d	projected;
	float		scale;

	scale = calculate_scale(render->map) * render->zoom_factor;
	projected.x = (int)(point.y * scale) + WINDOW_WIDTH / 2 + render->offset_x;
	projected.y = (int)(-point.z * scale) + WINDOW_HEIGHT / 2
		+ render->offset_y;
	if (point.color == -1)
		projected.color = COLOR_WHITE;
	else
		projected.color = point.color;
	return (projected);
}

void	cycle_projection(t_render *render)
{
	render->projection_type = (render->projection_type + 1) % PROJ_COUNT;
}
