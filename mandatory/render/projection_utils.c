/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 20:33:18 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "printf.h"
#include "render.h"
#include "utils.h"
#include <math.h>

static float	deg_to_rad(float degree)
{
	return (degree * M_PI / 180.0f);
}

t_point2d	calculate_projection_coords(t_point point, float scale,
		float z_factor, t_map *map)
{
	t_point2d	projected;
	float		centered_x;
	float		centered_y;

	centered_x = point.x - (map->width - 1) / 2.0f;
	centered_y = point.y - (map->height - 1) / 2.0f;
	projected.x = (centered_x + centered_y) * cos(deg_to_rad(30)) * scale
		+ WINDOW_WIDTH / 2;
	projected.y = (centered_y - centered_x - point.z * z_factor)
		* sin(deg_to_rad(30)) * scale + WINDOW_HEIGHT / 2;
	return (projected);
}

int	set_point_color(int original_color)
{
	if (original_color == -1)
		return (COLOR_WHITE);
	else
		return (original_color);
}
