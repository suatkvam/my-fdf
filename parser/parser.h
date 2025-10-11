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

int			open_file(const char *file_name);
int			is_valid_file(const char *path);
char		**read_file(int fd);
int			count_cells(const char *line);
int			check_map_valid(char **lines);
t_point		parse_token(char *token, int x, int y);
t_map		*map_parser(const char *file_name);
t_map		*create_empty_map(int width, int height);
void		free_map(t_map *map);

#endif