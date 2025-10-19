/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_specific_factors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:30:00 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 20:53:05 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static float	calculate_small_map_z_factor(t_map *map)
{
	if ((map->width == 10 && map->height == 10))
		return (0.8);
	if (map->width == 10 && map->height == 13)
		return (1.8);
	if (map->width == 11 && map->height == 9)
		return (1.5);
	if (map->width == 19 && map->height == 11)
		return (1.2);
	if (map->width == 20 && map->height == 20)
		return (0.5);
	if (map->width == 21 && map->height == 9)
		return (1.0);
	return (1.0);
}

static float	calculate_large_map_z_factor(t_map *map)
{
	if (map->width == 27 && map->height == 27)
		return (0.8);
	if (map->width == 27 && map->height == 34)
		return (1.6);
	if (map->width == 48 && map->height == 47)
		return (0.5);
	if (map->width == 50 && map->height == 50)
		return (0.4);
	if (map->width == 100 && map->height == 100)
		return (0.6);
	if (map->width == 200 && map->height == 116)
		return (0.3);
	if (map->width == 200 && map->height == 200)
		return (0.25);
	if (map->width == 500 && map->height == 500)
		return (0.2);
	return (0.5);
}

float	calculate_z_factor(t_map *map)
{
	int	max_dimension;

	if (map->width > map->height)
		max_dimension = map->width;
	else
		max_dimension = map->height;
	if (max_dimension <= 25)
		return (calculate_small_map_z_factor(map));
	else
		return (calculate_large_map_z_factor(map));
}
