#include "parser.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_map	*create_empty_map(int width, int height)
{
	t_map	*map;
	int		i;
	int		j;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	
	map->width = width;
	map->height = height;
	
	// Allocate array of row pointers
	map->grid = (t_point **)malloc(sizeof(t_point *) * height);
	if (!map->grid)
	{
		free(map);
		return (NULL);
	}
	
	// Allocate each row
	i = 0;
	while (i < height)
	{
		map->grid[i] = (t_point *)malloc(sizeof(t_point) * width);
		if (!map->grid[i])
		{
			// Free already allocated rows
			j = 0;
			while (j < i)
			{
				free(map->grid[j]);
				j++;
			}
			free(map->grid);
			free(map);
			return (NULL);
		}
		
		// Initialize points to zero
		j = 0;
		while (j < width)
		{
			map->grid[i][j].x = j;
			map->grid[i][j].y = i;
			map->grid[i][j].z = 0;
			map->grid[i][j].color = 0xFFFFFF; // White default
			j++;
		}
		i++;
	}
	
	return (map);
}