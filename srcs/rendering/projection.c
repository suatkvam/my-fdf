/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by akivam            #+#    #+#             */
/*   Updated: 2025/09/16 14:32:49 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
** Applies isometric projection to transform 3D coordinates to 2D screen space.
** Uses standard isometric angles (30 degrees) for proper 3D visualization.
** Z-axis is scaled down to prevent excessive vertical displacement.
*/

void	projection(t_point_coordinate *point)
{
	int		previous_x;
	int		previous_y;
	double	z_scale;

	previous_x = point->x;
	previous_y = point->y;
	z_scale = 0.5;
	point->x = (previous_x - previous_y) * 0.866;
	point->y = (previous_x + previous_y) * 0.5 - (point->z * z_scale);
}