#include "parser.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file.fdf>\n", argv[0]);
		return 1;
	}

	/* TODO: call parser/load map here */
	(void)argv;
	return 0;
}
