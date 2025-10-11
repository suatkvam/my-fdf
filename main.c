#include "libft.h"
#include "parser.h"
#include "printf.h"
#include "utils.h"
#include "render.h"
#include "format/format.h"
#include <sys/time.h>
#include <stdio.h>

static void	print_parse_time(long time_taken)
{
	if (time_taken < 1000)
		printf("Parse time: %ld microseconds\n", time_taken);
	else if (time_taken < 1000000)
		printf("Parse time: %.2f milliseconds\n", time_taken / 1000.0);
	else if (time_taken < 60000000)
		printf("Parse time: %.3f seconds\n", time_taken / 1000000.0);
	else
		printf("Parse time: %.2f minutes\n", time_taken / 60000000.0);
}

static int	has_extension(const char *path, const char *ext)
{
	size_t path_len, ext_len;
	if (!path || !ext)
		return (0);
	path_len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (path_len < ext_len)
		return (0);
	return (ft_strncmp(path + path_len - ext_len, ext, ext_len) == 0);
}

t_map	*mesh_to_fdf_grid(t_mesh *mesh, int grid_size)
{
	t_map	*map;
	int		i, x, y;
	float	min_x, max_x, min_y, max_y, scale_x, scale_y;
	
	if (!mesh || mesh->vertex_count == 0)
		return (NULL);
	
	// Find bounds
	min_x = max_x = mesh->vertices[0].position.x;
	min_y = max_y = mesh->vertices[0].position.y;
	i = 1;
	while (i < mesh->vertex_count)
	{
		if (mesh->vertices[i].position.x < min_x) min_x = mesh->vertices[i].position.x;
		if (mesh->vertices[i].position.x > max_x) max_x = mesh->vertices[i].position.x;
		if (mesh->vertices[i].position.y < min_y) min_y = mesh->vertices[i].position.y;
		if (mesh->vertices[i].position.y > max_y) max_y = mesh->vertices[i].position.y;
		i++;
	}
	
	// Allocate grid
	map = create_empty_map(grid_size, grid_size);
	if (!map)
		return (NULL);
		
	scale_x = (max_x - min_x) / (grid_size - 1);
	scale_y = (max_y - min_y) / (grid_size - 1);
	
	// Project vertices to grid with interpolation
	i = 0;
	while (i < mesh->vertex_count)
	{
		x = (int)((mesh->vertices[i].position.x - min_x) / scale_x);
		y = (int)((mesh->vertices[i].position.y - min_y) / scale_y);
		if (x >= 0 && x < grid_size && y >= 0 && y < grid_size)
		{
			map->grid[y][x].z = (int)(mesh->vertices[i].position.z * 10);
			map->grid[y][x].color = mesh->vertices[i].color;
		}
		i++;
	}
	
	return (map);
}

int	parse_and_render_map(const char *map_file)
{
	t_map			*map;
	t_render		*render;
	struct timeval	start, end;
	long			time_taken;
	t_mesh			*mesh;

	ft_printf("Starting to parse: %s\n", map_file);
	gettimeofday(&start, NULL);
	
	// Check file type and parse accordingly
	if (has_extension(map_file, ".stl"))
	{
		ft_printf("Detected STL file, loading mesh...\n");
		mesh = load_stl_file(map_file);
		if (!mesh)
		{
			ft_printf("Error: Could not load STL file %s\n", map_file);
			return (1);
		}
		ft_printf("STL loaded: %d vertices, %d faces\n", mesh->vertex_count, mesh->face_count);
		map = mesh_to_fdf_grid(mesh, 50); // 50x50 grid
		free_mesh(mesh);
	}
	else
	{
		map = map_parser(map_file);
	}
	
	gettimeofday(&end, NULL);
	time_taken = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
	
	if (!map)
	{
		ft_printf("Error: Could not parse map %s\n", map_file);
		return (1);
	}
	ft_printf("Map parsed successfully: %dx%d\n", map->width, map->height);
	print_parse_time(time_taken);
	ft_printf("Example point [0][0]: z=%d, color=%d\n", map->grid[0][0].z,
		map->grid[0][0].color);
		
	// Initialize render system
	ft_printf("Initializing render system...\n");
	render = init_render(map);
	if (!render)
	{
		ft_printf("Error: Could not initialize render system\n");
		free_map(map);
		return (1);
	}
	ft_printf("Render system initialized successfully\n");
	
	// Start rendering
	ft_printf("Starting render loop...\n");
	start_render(render);
	
	// Cleanup is handled by event handlers when window closes
	return (0);
}

int	main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.fdf>\n", argv[0]);
		return (1);
	}
	if (!is_valid_file(argv[1]))
	{
		ft_printf("Invalid map file (must end with %s): %s\n", MAP_EXTENSION,
			argv[1]);
		return (1);
	}
	
	return (parse_and_render_map(argv[1]));
}