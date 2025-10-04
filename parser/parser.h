#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

#ifndef MAP_EXTENSION
#define MAP_EXTENSION ".fdf"
#endif


int	open_file(const char *file_name);
int	is_valid_file(const char *path);
char	**read_file(int fd);
int	count_cells(const char *line);
int	check_map_valid(char **lines);

#endif