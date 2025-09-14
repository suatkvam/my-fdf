#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"
#include "pars.h"
#include <ctype.h>  // isspace için



static void	init_map_data(t_get_map_dimensions *data)
{
	data->expected_columns = -1;
	data->line_num = 0;
	data->fd = -1;
	data->line = NULL;
	data->split_lines = NULL;
}

static int	count_cells(const char *line)
{
	int	count = 0;
	int	i = 0;
	int	in_cell = 0;

	while (line[i])
	{
		if (!isspace(line[i]) && !in_cell)
		{
			in_cell = 1;
			count++;
		}
		else if (isspace(line[i]))
			in_cell = 0;
		i++;
	}
	return (count);
}

static int	process_line(t_get_map_dimensions *data)
{
	int	cells;

	if (!data->line)
		return (0);

	cells = count_cells(data->line);
	if (cells == 0)
		return (-1); // boş satır hatası

	if (data->expected_columns == -1)
		data->expected_columns = cells;
	else if (cells != data->expected_columns)
		return (free(data->line), -1);

	free(data->line);
	data->line_num++;
	return (0);
}

int	get_map_dimensions(const char *file_name)
{
	t_get_map_dimensions	data;

	init_map_data(&data);
	data.fd = open_file(file_name);
	if (data.fd < 0)
		return (perror("Error opening file"), -2);

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
