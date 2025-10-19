/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:45:25 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "render.h"

t_point2d	project_point_scaled(t_point point, t_map *map)
{
	t_point2d	projected;
	float		scale;
	float		z_factor;

	scale = calculate_scale(map);
	z_factor = calculate_z_factor(map);
	projected = calculate_projection_coords(point, scale, z_factor, map);
	projected.color = set_point_color(point.color);
	return (projected);
}

t_point2d	project_point(t_point point, t_map *map)
{
	t_point2d	projected;
	float		scale;

	scale = 20.0;
	projected = calculate_projection_coords(point, scale, 0.3, map);
	projected.color = set_point_color(point.color);
	return (projected);
}
