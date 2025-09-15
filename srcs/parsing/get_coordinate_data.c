#include "draw.h"
#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"
#include "pars.h"
#include <stdio.h>
#include <stdlib.h>

static void	fiil_coordinates(int fd, t_point_coordinate *coordinates, int width)
{
	char	*line;
	char	**split_line;
	int		x;
	int		y;

	y = 0;
	while ((line = get_next_line(fd)))
	{
		split_line = ft_split(line, ' ');
		free(line);
		x = 0;
		while (split_line[x] && *split_line[x] != '\n')
		{
			coordinates[y * width + x].x = x;
			coordinates[y * width + x].y = y;
			coordinates[y * width + x].z = ft_atoi(split_line[x]);
			free(split_line[x]);
			x++;
		}
		free(split_line);
		y++;
	}
}

// Ana fonksiyon
t_point_coordinate	*get_coordinates(const char *file_name, t_map_data map)
{
	t_point_coordinate	*coordinates;
	int					fd;
	int					total_size;

	if (map.width <= 0 || map.height <= 0)
		return (NULL);
	total_size = map.width * map.height;
	coordinates = malloc(sizeof(t_point_coordinate) * (total_size));
	if (!coordinates)
		return (NULL);
	fd = open_file(file_name);
	if (fd < 0)
	{
		perror("open_file");
		free(coordinates);
		return (NULL);
	}
	fiil_coordinates(fd, coordinates, map.width);
	close(fd);
	return (coordinates);
}
