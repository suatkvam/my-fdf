/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 18:03:29 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "printf.h"
#include "libft.h"
#include "parser.h"
#include "render.h"
#include "utils.h"
#include <stdlib.h>
#include "../colors/colors.h"

void	handle_child_process(char *map_path)
{
	process_single_map(map_path);
	exit(0);
}

void	handle_parent_process(char *map_path, t_proc_info *proc, pid_t pid)
{
	char	*map_name;
	char	*display_name;

	(*proc->child_processes)++;
	(*proc->launched)++;
	map_name = extract_map_name(map_path);
	if (map_name)
		display_name = map_name;
	else
		display_name = map_path;
	ft_printf(ANSI_COLOR_GREEN "SUCCESS:" ANSI_COLOR_RESET \
		" Launching window for " ANSI_COLOR_BOLD "'%s'" \
		ANSI_COLOR_RESET " (PID: %d)\n", display_name, pid);
	if (map_name)
		free(map_name);
}
