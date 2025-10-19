/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:56:12 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdlib.h"
#include "utils.h"
#include <stdio.h>

int	parse_row_tokens(t_parser_data *data)
{
	data->j = 0;
	while (data->j < data->map->width && data->tokens[data->j])
	{
		data->map->grid[data->i][data->j] = parse_token(data->tokens[data->j],
				data->j, data->i);
		data->j++;
	}
	return (0);
}

int	process_single_row(t_parser_data *data)
{
	data->map->grid[data->i] = malloc(sizeof(t_point) * data->map->width);
	if (!data->map->grid[data->i])
	{
		free_partial_map(data->map, data->i);
		ft_free_split(data->lines);
		return (-1);
	}
	data->tokens = ft_split(data->lines[data->i], ' ');
	if (!data->tokens)
	{
		free_partial_map(data->map, data->i + 1);
		ft_free_split(data->lines);
		return (-1);
	}
	if (parse_row_tokens(data) != 0)
	{
		ft_free_split(data->tokens);
		free_partial_map(data->map, data->i + 1);
		ft_free_split(data->lines);
		return (-1);
	}
	ft_free_split(data->tokens);
	return (0);
}

int	process_map_rows(t_parser_data *data)
{
	data->i = 0;
	while (data->i < data->map->height)
	{
		if (process_single_row(data) != 0)
			return (-1);
		data->i++;
	}
	return (0);
}

t_map	*map_parser(const char *file_name)
{
	t_parser_data	data;

	if (init_parser_data(&data, file_name) != 0)
		return (NULL);
	if (!create_map_structure(&data))
		return (NULL);
	if (allocate_map_grid(&data) != 0)
		return (NULL);
	if (process_map_rows(&data) != 0)
		return (NULL);
	ft_free_split(data.lines);
	return (data.map);
}
