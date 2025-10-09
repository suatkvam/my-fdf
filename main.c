#include "libft.h"
#include "parser.h"
#include "printf.h"
#include "utils.h"
#include "render.h"
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

int	parse_and_render_map(const char *map_file)
{
	t_map			*map;
	t_render		*render;
	struct timeval	start, end;
	long			time_taken;

	ft_printf("Starting to parse: %s\n", map_file);
	gettimeofday(&start, NULL);
	
	map = map_parser(map_file);
	
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