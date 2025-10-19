/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 18:00:31 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "printf.h"
#include "./render/render.h"
#include "utils.h"
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include "./colors/colors.h"
#include "main.h"

int	render_and_start(t_map *map, char *map_name)
{
	t_render	*render;

	render = init_render(map, map_name);
	if (!render)
	{
		free_map(map);
		return (1);
	}
	start_render(render, map_name);
	return (0);
}

int	main(int argc, char **argv)
{
	int	child_processes;
	int	launched;

	if (argc < 2)
	{
		ft_printf("Usage: %s <map_file.fdf> [map_file2.fdf] ...\n", argv[0]);
		return (1);
	}
	launched = launch_maps(argc, argv, &child_processes);
	if (launched <= 0)
	{
		ft_err_printf(ANSI_COLOR_RED "Error:" ANSI_COLOR_RESET
			" No valid maps were processed\n");
		return (1);
	}
	wait_for_children(child_processes);
	return (0);
}
