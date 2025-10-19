/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:53:02 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "parser.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static char	**copy_lines_to_new_array(char **lines, int count)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (count + 2));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < count && lines)
	{
		temp[i] = lines[i];
		i++;
	}
	return (temp);
}

static char	**read_lines_loop(int fd, char **lines, int *count)
{
	char	*line;
	char	**temp;

	line = get_next_line(fd);
	while (line != NULL)
	{
		temp = copy_lines_to_new_array(lines, *count);
		if (!temp)
		{
			free(line);
			if (lines)
				ft_free_split(lines);
			return (NULL);
		}
		if (lines)
			free(lines);
		temp[*count] = line;
		temp[(*count) + 1] = NULL;
		lines = temp;
		(*count)++;
		line = get_next_line(fd);
	}
	return (lines);
}

char	**read_file(int fd)
{
	char	**lines;
	int		count;

	lines = NULL;
	count = 0;
	if (fd < 0)
	{
		perror("");
		return (NULL);
	}
	lines = read_lines_loop(fd, lines, &count);
	get_next_line(-1);
	if (!lines)
	{
		return (NULL);
	}
	return (lines);
}
