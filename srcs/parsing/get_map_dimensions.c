#include "fdf.h"
#include "libft.h"
#include "pars.h"
#include "get_next_line.h"

static void	free_split_and_line(char **split_lines, char *line)
{
	int	i;

	i = 0;
	while (split_lines[i])
		free(split_lines[i++]);
	free(split_lines);
	free(line);
}
static void	init_map_data(t_get_map_dimensions *data)
{
	data->expected_columns = -1;
	data->line_num = 0;
	data->fd = -1;
	data->line = NULL;
	data->split_lines = NULL;
}
static int	process_line(t_get_map_dimensions *data)
{
	data->split_lines = ft_split(data->line, ' ');
	data->current_columns = 0;
	while (data->split_lines[data->current_columns])
		data->current_columns++;
	if (data->expected_columns == -1)
		data->expected_columns = data->current_columns;
	else if (data->current_columns != data->expected_columns)
	{
		free_split_and_line(data->split_lines, data->line);
		return (-1);
	}
	free_split_and_line(data->split_lines, data->line);
	data->line_num++;
	return (0);
}

int	get_map_dimensions(const char *file_name)
{
	t_get_map_dimensions data;

	init_map_data(&data);
	data.fd = open_file(file_name);
	if (data.fd < 0)
		return (perror("Error opening file"), -2);
	// Virgül operatörü ile birleştirme

	data.line = get_next_line(data.fd);
	while (data.line)
	{
		if (process_line(&data) == -1)
			return (close(data.fd), -1);
		data.line = get_next_line(data.fd);
	}
	close(data.fd);
	if (data.expected_columns == -1)
		data.expected_columns = 0;
	return (data.line_num * data.expected_columns);
}