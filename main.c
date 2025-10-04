#include "libft.h"
#include "parser.h"
#include "printf.h"

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
	/* TODO: call parser/load map here */
	(void)argv;
	return (0);
}
