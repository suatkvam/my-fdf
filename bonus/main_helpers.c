/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2026/03/23 13:46:30 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./colors/colors.h"
#include "main.h"

t_map	*parse_map(const char *map_file)
{
	t_map	*map;
	char	*map_name;

	map_name = extract_map_name(map_file);
	map = map_parser(map_file);
	if (!map)
		return (parse_map_error(map_name));
	if (map_name)
		free(map_name);
	return (map);
}

void	wait_for_children(int child_processes)
{
	while (child_processes > 0)
	{
		wait(NULL);
		child_processes--;
	}
	ft_printf(ANSI_COLOR_GREEN "COMPLETE:" ANSI_COLOR_RESET \
		" All windows closed. Goodbye!\n");
}

int	launch_maps(int argc, char **argv, int *child_processes)
{
	int			i;
	t_proc_info	proc;
	int			launched;

	launched = 0;
	*child_processes = 0;
	proc.launched = &launched;
	proc.child_processes = child_processes;
	i = 1;
	while (i < argc)
	{
		if (!is_valid_file(argv[i]))
		{
			ft_err_printf(ANSI_COLOR_YELLOW "Warning:" ANSI_COLOR_RESET \
				" Invalid map file '%s' - skipping\n", argv[i]);
			i++;
			continue ;
		}
		launch_map_child(argv[i], &proc);
		i++;
	}
	return (launched);
}

int	process_single_map(const char *map_file)
{
	t_map	*map;
	char	*map_name;

	map = parse_map(map_file);
	if (!map)
		return (0);
	map_name = extract_map_name(map_file);
	if (!map_name)
	{
		free_map(map);
		return (0);
	}
	render_and_start(map, map_name);
	return (1);
}
