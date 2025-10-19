/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 17:59:26 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "colors.h"

int	get_max_dimension(t_map *map)
{
	if (!map)
		return (5);
	if (map->width > map->height)
		return (map->width);
	else
		return (map->height);
}

float	calculate_scale(t_map *map)
{
	int	max_dimension;

	if (!map)
		return (20.0);
	max_dimension = get_max_dimension(map);
	if (max_dimension <= 5)
		return (100.0);
	else if (max_dimension <= 10)
		return (50.0);
	else if (max_dimension <= 15)
		return (35.0);
	else if (max_dimension <= 25)
		return (25.0);
	else if (max_dimension <= 35)
		return (15.0);
	else if (max_dimension <= 50)
		return (12.0);
	else if (max_dimension <= 100)
		return (6.0);
	else if (max_dimension <= 200)
		return (3.0);
	else
		return (1.0);
}

int	set_point_color(int original_color)
{
	if (original_color == -1)
		return (COLOR_WHITE);
	else
		return (original_color);
}
