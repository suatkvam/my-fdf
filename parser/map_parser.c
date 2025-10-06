#include "parser.h"
#include "stdlib.h"
#include "utils.h"

static void	free_partial_map(t_map *map, int allocated_rows)
{
	int	i;

	i = 0;
	while (i < allocated_rows)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}

t_map	*map_parser(const char *file_name)
{
	int		fd;
	char	**lines;
	t_map	*map;
	char	**tokens;
	int		i;
	int		j;

	fd = open_file(file_name); // kendi hata döndürüyor null diye
	if (fd < 0)
	{
		perror("");
		return (NULL);
	}
	lines = read_file(fd);
	close(fd);
	if (!lines || check_map_valid(lines) != 0)
	{
		if (lines)
			ft_free_split(lines);
		return (NULL);
	}
	map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_free_split(lines);
		return (NULL);
	}
	// get dimension
	map->height = 0;
	while (lines[map->height])
		map->height++;
	map->width = count_cells(lines[0]);
	// Allocate grid
	map->grid = malloc(sizeof(t_point *) * map->height);
	if (!map->grid)
	{
		ft_free_split(lines);
		free(map);
		return (NULL);
	}
	// parse each line
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc(sizeof(t_point) * map->width);
		if (!map->grid[i])
		{
			free_partial_map(map, i);
			ft_free_split(lines);
			return (NULL);
		}
		tokens = ft_split(lines[i], ' ');
		if (!tokens)
		{
			free_partial_map(map, i + 1);
			ft_free_split(lines);
			return (NULL);
		}
		j = 0;
		while (j < map->width && tokens[j])
		{
			map->grid[i][j] = parse_token(tokens[j], j, i);
			j++;
		}
		ft_free_split(tokens);
		i++;
	}
	ft_free_split(lines);
	return (map);
}
