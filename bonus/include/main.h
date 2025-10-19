/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 18:01:57 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "colors.h"
# include "libft.h"
# include "parser.h"
# include "printf.h"
# include "render.h"
# include <math.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_proc_info
{
	int		*child_processes;
	int		*launched;
}			t_proc_info;

typedef struct s_angle_vars
{
	float	ux;
	float	uy;
	float	vx;
	float	vy;
	float	dot;
	float	norm_u;
	float	norm_v;
}			t_angle_vars;

int			render_and_start(t_map *map, char *map_name);
t_map		*parse_map(const char *map_file);
t_map		*parse_map_error(char *map_name);
int			count_colored(t_map *map);
float		compute_xy_angle(float scale);
char		*extract_map_name(const char *filepath);
int			process_single_map(const char *map_file);

void		wait_for_children(int child_processes);
int			launch_maps(int argc, char **argv, int *child_processes);
int			render_and_start(t_map *map, char *map_name);
int			launch_map_child(char *map_path, t_proc_info *proc);
int			is_valid_file(const char *filepath);
void		free_map(t_map *map);

#endif