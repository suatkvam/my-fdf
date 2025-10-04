#include "parser.h"
#include <stdlib.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

int count_cells(const char *line)
{
    int count = 0;
    int i = 0;
    int in_cell = 0;

    while (line[i])
    {
        if (!ft_isspace(line[i]) && !in_cell)
        {
            in_cell = 1;
            count++;
        }
        else if (ft_isspace(line[i]))
            in_cell = 0;
        i++;
    }
    return count;
}
