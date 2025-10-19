/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:56:09 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdlib.h"
#include "utils.h"
#include <stdio.h>

void	free_partial_map(t_map *map, int allocated_rows)
{
	int	i;

	i = 0;
	while (i < allocated_rows)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}

int	init_parser_data(t_parser_data *data, const char *file_name)
{
	data->fd = open_file(file_name);
	if (data->fd < 0)
	{
		perror("");
		return (-1);
	}
	data->lines = read_file(data->fd);
	close(data->fd);
	if (!data->lines || check_map_valid(data->lines) != 0)
	{
		if (data->lines)
			ft_free_split(data->lines);
		return (-1);
	}
	return (0);
}

t_map	*create_map_structure(t_parser_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		ft_free_split(data->lines);
		return (NULL);
	}
	data->map->height = 0;
	while (data->lines[data->map->height])
		data->map->height++;
	data->map->width = count_cells(data->lines[0]);
	return (data->map);
}

int	allocate_map_grid(t_parser_data *data)
{
	data->map->grid = malloc(sizeof(t_point *) * data->map->height);
	if (!data->map->grid)
	{
		ft_free_split(data->lines);
		free(data->map);
		return (-1);
	}
	return (0);
}
