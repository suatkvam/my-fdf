/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:46:15 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "printf.h"
#include "render.h"
#include "utils.h"
#include "colors.h"
#include <stdio.h>

static int	count_colored(t_map *map);

t_map	*parse_map(const char *map_file)
{
	t_map	*map;
	int		colored;

	map = map_parser(map_file);
	if (!map)
	{
		ft_err_printf("Error: Could not parse map %s\n", map_file);
		return (NULL);
	}
	ft_printf(ANSI_GREEN "Map parsed successfully: %dx%d" ANSI_RESET "\n", \
		map->width, map->height);
	colored = count_colored(map);
	ft_printf(ANSI_CYAN "Total colored points (color != -1): %d" \
		ANSI_RESET "\n", colored);
	ft_printf(ANSI_YELLOW "Projection isometric angle: \
		%d degrees" ANSI_RESET "\n", (int)get_isometric_axes_angle_deg());
	ft_printf(ANSI_YELLOW "Projection angle: %d degrees" ANSI_RESET "\n", \
		(int)get_projection_axes_angle_deg());
	return (map);
}

static int	count_colored(t_map *map)
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

int	render_and_start(t_map *map)
{
	t_render	*render;

	ft_printf(ANSI_BLUE "Initializing render system..." ANSI_RESET "\n");
	render = init_render(map);
	if (!render)
	{
		ft_err_printf("Error: Could not initialize render system\n");
		free_map(map);
		return (1);
	}
	ft_printf(ANSI_GREEN "Render system initialized successfully" \
		ANSI_RESET "\n");
	ft_printf(ANSI_MAGENTA "Starting render loop..." ANSI_RESET "\n");
	start_render(render);
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_map	*map;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.fdf>\n", argv[0]);
		return (1);
	}
	if (!is_valid_file(argv[1]))
	{
		ft_printf("Invalid map file (must end with %s): %s\n", MAP_EXTENSION,
			argv[1]);
		return (1);
	}
	map = parse_map(argv[1]);
	if (!map)
		return (1);
	return (render_and_start(map));
}
