#include "fdf.h"
#include "libft.h"
#include "pars.h"

static void	free_split_and_line(char **split_lines, char *line)
{
	int	i;

	i = 0;
	while (split_lines[i])
		free(split_lines[i++]);
	free(split_lines);
	free(line);
}

int	get_map_dimensions(const char *file_name)
{
	t_get_map_dimensions	map_data;

	map_data.expected_columns = -1;
	map_data.line_num = 0;
	map_data.fd = open_file(file_name);
	if (map_data.fd < 0)
	{
		perror("Error opening file");
		return (-2);
	}
	// file can't open
	map_data.line = get_next_line(map_data.fd);
	while (map_data.line)
	{
		map_data.split_lines = ft_split(map_data.line, ' ');
		map_data.current_columns = 0;
		while (map_data.split_lines[map_data.current_columns++])
			;
		if (map_data.expected_columns == -1)
			map_data.expected_columns = map_data.current_columns;
		else if (map_data.current_columns != map_data.expected_columns)
			return (free_split_and_line(map_data.split_lines, map_data.line),
				close(map_data.fd), -1);
		free_split_and_line(map_data.split_lines, map_data.line);
		map_data.line_num++;
		map_data.line = get_next_line(map_data.fd);
	}
	close(map_data.fd);
	return (map_data.line_num * map_data.expected_columns);
}
