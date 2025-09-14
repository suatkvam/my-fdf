#include "draw.h"
#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"
#include "pars.h"
#include <stdio.h>
#include <stdlib.h>

static void	process_line(t_get_coordinates *data)
{
	int		col;
	char	**split_lines;

	col = 0;
	split_lines = ft_split(data->line, ' ');
	free(data->line);
	while (split_lines[col])
	{
		data->coordinates[data->index].x = col;
		data->coordinates[data->index].y = data->row;
		data->coordinates[data->index].z = ft_atoi(split_lines[col]);
		// ya da ft_atoi_base
		free(split_lines[col]);
		col++;
		data->index++;
	}
	free(split_lines);
}

// Ana fonksiyon
t_point_coordinate	*get_coordinates(const char *file_name, int *total_cells)
{
	t_get_coordinates	data;

	data.width = get_map_dimensions(file_name) / 2;
	data.height = get_map_dimensions(file_name) / 2;
	*total_cells = data.width * data.height;
	data.coordinates = malloc(sizeof(t_point_coordinate) * (*total_cells));
	if (!data.coordinates)
		return (NULL);
	data.fd = open_file(file_name);
	if (data.fd < 0)
	{
		perror("open_file");
		free(data.coordinates);
		return (NULL);
	}
	data.row = 0;
	data.index = 0;
	data.line = get_next_line(data.fd);
	while (data.line)
	{
		process_line(&data);
		data.row++;
		data.line = get_next_line(data.fd);
	}
	return (close(data.fd), data.coordinates);
}
