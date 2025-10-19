/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 18:00:47 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "libft.h"
#include "main.h"
#include "parser.h"
#include "printf.h"
#include "render.h"
#include <math.h>
#include <sys/wait.h>

int	count_colored(t_map *map)
{
	int	x;
	int	y;
	int	colored;

	y = 0;
	colored = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x].color != -1)
				++colored;
			++x;
		}
		++y;
	}
	return (colored);
}

float	compute_xy_angle(float scale)
{
	t_angle_vars	v;

	v.ux = scale;
	v.uy = scale * 0.5f;
	v.vx = -scale;
	v.vy = scale * 0.5f;
	v.dot = v.ux * v.vx + v.uy * v.vy;
	v.norm_u = sqrtf(v.ux * v.ux + v.uy * v.uy);
	v.norm_v = sqrtf(v.vx * v.vx + v.vy * v.vy);
	if (v.norm_u == 0 || v.norm_v == 0)
		return (0.0f);
	return (acosf(v.dot / (v.norm_u * v.norm_v)));
}
