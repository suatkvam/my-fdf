#include "parser.h"
#include <ctype.h>
#include <stdlib.h>

int count_cells(const char *line)
{
    int count = 0;
    int i = 0;
    int in_cell = 0;

    while (line[i])
    {
        if (!isspace(line[i]) && !in_cell)
        {
            in_cell = 1;
            count++;
        }
        else if (isspace(line[i]))
            in_cell = 0;
        i++;
    }
    return count;
}
