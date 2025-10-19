/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 18:03:57 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "../colors/colors.h"
#include "process.h"

static void	handle_fork_failure(char *map_path)
{
	ft_err_printf(ANSI_COLOR_RED "Error:" ANSI_COLOR_RESET \
		" Fork failed for map: %s\n", map_path);
}

int	launch_map_child(char *map_path, t_proc_info *proc)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_child_process(map_path);
	else if (pid > 0)
		handle_parent_process(map_path, proc, pid);
	else
		handle_fork_failure(map_path);
	return (0);
}
