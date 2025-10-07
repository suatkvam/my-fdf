#include "get_next_line.h"
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
	while (i < count)
	{
		temp[i] = lines[i];
		i++;
	}
	return (temp);
}

static char	**read_lines_loop(int fd, char **lines, int count)
{
	char	*line;
	char	**temp;

	while ((line = get_next_line(fd)) != NULL)
	{
		temp = copy_lines_to_new_array(lines, count);
		if (!temp)
		{
			free(line);
			ft_free_split(lines);
			return (NULL);
		}
		free(lines);
		temp[count] = line;
		temp[count + 1] = NULL;
		lines = temp;
		count++;
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
	lines = read_lines_loop(fd, lines, count);
	
	// Clear GNL's static stash by calling with invalid fd
	get_next_line(-1);
	
	if (!lines)
	{
		printf("Dosya boş!\n");
		return (NULL);
	}
	return (lines);
}
