#include "libft.h"
#include "parser.h"
#include "printf.h"
#include "utils.h"

int	parse_and_render_map(const char *map_file)
{
	int		fd;
	char	**lines;
	int		result;

	fd = open_file(map_file);
	if (fd < 0)
	{
		ft_printf("Error: Could not open file %s\n", map_file);
		return (1);
	}
	lines = read_file(fd);
	close(fd);
	if (!lines)
	{
		ft_printf("Error: Could not read file %s\n", map_file);
		return (1);
	}
	result = check_map_valid(lines);
	if (result != 0)
	{
		ft_free_split(lines);
		return (1);
	}
	ft_printf("Map validated successfully: %s\n", map_file); // ! bunları en son temizle
	// TODO: Call render function here
	ft_free_split(lines);
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
		ft_printf("Invalid map file (must end with %s): %s\n",
			MAP_EXTENSION, argv[1]);
		return (1);
	}

	return (parse_and_render_map(argv[1]));
}
