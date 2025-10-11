#include "format.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* existing fd-based loader implemented in read_stl_file.c */
extern t_mesh	*load_stl_file_fd(int fd, uint32_t triangle_count);
/* ASCII loader may be implemented later; keep a stub */
extern t_mesh	*load_stl_ascii_file(const char *filename);

t_mesh	*load_stl_file(const char *filename)
{
	int				fd;
	unsigned char	header[80];
	uint32_t		tri_count;
	struct stat		st;
	off_t			expected;
	t_mesh			*m;

	if (!filename)
	{
		printf("Error: filename is NULL\n");
		errno = EINVAL;
		return (NULL);
	}
	printf("Trying to open file: %s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (NULL);
	}
	printf("Reading header to detect format...\n");
	if (read_binary_chunk(fd, header, 80) != 80)
	{
		printf("Failed to read header, trying ASCII mode\n");
		close(fd);
		return (load_stl_ascii_file(filename));
	}
	
	// Check if it starts with "solid" (ASCII format)
	if (strncmp((char *)header, "solid", 5) == 0)
	{
		printf("Detected ASCII STL format\n");
		close(fd);
		return (load_stl_ascii_file(filename));
	}
	
	printf("Detected binary STL format, reading triangle count...\n");
	if (read_uint32_le(fd, &tri_count) != 0)
	{
		printf("Failed to read triangle count, trying ASCII mode\n");
		close(fd);
		return (load_stl_ascii_file(filename));
	}
	printf("Triangle count: %u\n", tri_count);
	if (fstat(fd, &st) == 0)
	{
		expected = 84 + (off_t)tri_count * 50;
		if (st.st_size == expected)
		{
			m = load_stl_file_fd(fd, tri_count);
			close(fd);
			return (m);
		}
	}
	close(fd);
	return (load_stl_ascii_file(filename));
}
