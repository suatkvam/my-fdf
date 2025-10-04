#include "parser.h"

int	open_file(const char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("Error"); //  buraya hata mesajı yazılacak
		return (-1);     // file not find
	}
	return (fd);
}