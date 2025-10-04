#include "parser.h"
#include <stdio.h>

static int	validate_all_lines(char **lines, int expected_cols)
{
	int	i;
	int	cols;

	i = 0;
	while (lines[i])
	{
		cols = count_cells(lines[i]);
		if (cols != expected_cols)
		{
			if (cols > expected_cols)
				printf("Found wrong line length. Exiting.\n");
			else
				printf("Found wrong column length. Exiting.\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

// Satır ve sütun kontrolü
int	check_map_valid(char **lines)
{
	int	expected_cols;

	if (!lines || !lines[0])
	{
		printf("Found wrong line length. Exiting.\n");
		return (-1); // boş dosya veya ilk satır yok
	}
	expected_cols = count_cells(lines[0]);
	if (expected_cols == 0)
	{
		printf("Found wrong line length. Exiting.\n");
		return (-1); // ilk satır boş
	}
	return (validate_all_lines(lines, expected_cols));
}
