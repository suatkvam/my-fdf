/*
 * Read exactly `len` bytes into buf (handles short reads and EINTR).
 * Returns number of bytes read (may be < len on EOF), or -1 on error.
 */
#include "format.h"
#include "libft.h"

ssize_t	read_binary_chunk(int fd, void *buffer, size_t len)
{
	ssize_t			total;
	ssize_t			read_byte;
	unsigned char	*p;

	total = 0;
	p = (unsigned char *)buffer;
	if (len == 0)
		return (0);
	while ((size_t)total < len)
	{
		read_byte = read(fd, p + total, len - (size_t)total);
		if (read_byte < 0)
		{
			if (errno == EINTR)
				continue ;
			return (-1);
		}
		if (read_byte == 0) /*EOF*/
			break ;
		total += read_byte;
	}
	return (total);
}

int	read_uint8(int fd, uint8_t *out)
{
	size_t	read_byte;

	read_byte = read_binary_chunk(fd, out, 1);
	if (read_byte != 1)
	{
		if (read_byte < 0)
		{
			/* read() already set errno */
		}
		else
		{
			errno = EIO;
		}
		return (-1);
	}
	return (0);
}

int	read_uint16_le(int fd, uint16_t *out)
{
	unsigned char	binary[2];
	ssize_t			read_byte;

	read_byte = read_binary_chunk(fd, binary, 2);
	if (read_byte != 2)
	{
		if (read_byte < 0)
		{
			/* read() already set errno */
		}
		else
		{
			errno = EIO;
		}
		return (-1);
	}
	*out = (uint16_t)binary[0] | ((uint16_t)binary[1] << 8);
	return (0);
}

int	read_uint32_le(int fd, uint32_t *out)
{
	unsigned char byte[4];
	ssize_t read_byte;
	read_byte = read_binary_chunk(fd, byte, 4);
	if (read_byte != 4)
	{
		if (read_byte < 0)
		{
			/* read() already set errno */
		}
		else
		{
			errno = EIO;
		}
		return (-1);
	}
	*out = (uint32_t)byte[0] | ((uint32_t)byte[1] << 8) | ((uint32_t)byte[2] << 16) | ((uint32_t)byte[3] << 24);
	return (0);
}
int read_float_le(int fd, float *out)
{
    uint32_t bits;
    if (read_uint32_le(fd, &bits) != 0)
        return -1;
    /* Safely copy bit pattern into float */
    ft_memcpy(out, &bits, sizeof(bits));
    return 0;
}