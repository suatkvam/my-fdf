#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"
#include "pars.h"
#include <ctype.h> // isspace için

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
	int	count;
	int	i;
	int	in_cell;

	count = 0;
	i = 0;
	in_cell = 0;
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
	if (cells == 0 && data->line[0] != '\n')
		return (-1); // boş satır hatası
	if (cells == 0 && data->line[0] == '\n')
		return (0);
	if (data->expected_columns == -1 && cells > 0)
		data->expected_columns = cells;
	else if (cells != 0 && cells != data->expected_columns)
		return (free(data->line), -1);
	if (cells > 0)
		data->line_num++;
	free(data->line);
	return (0);
}

static int	read_lines_and_process(t_get_map_dimensions *data,
		t_map_data *map_data)
{
	data->line = get_next_line(data->fd);
	while (data->line)
	{
		if (process_line(data) == -1)
		{
			map_data->width = 0;
			map_data->height = 0;
			while (get_next_line(data->fd))
				;
			return (-1);
		}
		data->line = get_next_line(data->fd);
	}
	return (0);
}

t_map_data	get_map_dimensions(const char *file_name)
{
	t_get_map_dimensions	data;
	t_map_data				map_data;

	map_data.width = 0;
	map_data.height = 0;
	init_map_data(&data);
	data.fd = open_file(file_name);
	if (data.fd < 0)
		return (map_data);
	if (read_lines_and_process(&data, &map_data) == -1)
	{
		close(data.fd);
		return (map_data);
	}
	close(data.fd);
	if (data.expected_columns == -1)
		map_data.width = 0;
	else
		map_data.width = data.expected_columns;
	map_data.height = data.line_num;
	return (map_data);
}
