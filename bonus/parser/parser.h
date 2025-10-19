/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 19:25:23 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>

# ifndef MAP_EXTENSION
#  define MAP_EXTENSION ".fdf"
# endif

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**grid;
}			t_map;

typedef struct s_parser_data
{
	int		fd;
	char	**lines;
	t_map	*map;
	char	**tokens;
	int		i;
	int		j;
}			t_parser_data;

int			open_file(const char *file_name);
int			is_valid_file(const char *path);
char		**read_file(int fd);
int			count_cells(const char *line);
int			check_map_valid(char **lines);
t_point		parse_token(char *token, int x, int y);
t_map		*map_parser(const char *file_name);
void		free_map(t_map *map);
void		free_partial_map(t_map *map, int allocated_rows);
int			init_parser_data(t_parser_data *data, const char *file_name);
t_map		*create_map_structure(t_parser_data *data);
int			allocate_map_grid(t_parser_data *data);

#endif
