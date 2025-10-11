#include "format.h"
#include <errno.h>
#include <fcntl.h>
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
		errno = EINVAL;
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (read_binary_chunk(fd, header, 80) != 80)
	{
		close(fd);
		return (NULL);
	}
	if (read_uint32_le(fd, &tri_count) != 0)
	{
		close(fd);
		return (load_stl_ascii_file(filename));
	}
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
