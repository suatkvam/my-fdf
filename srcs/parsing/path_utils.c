#include "fdf.h"

const char	*ft_basename(const char *path)
{
	const char	*p;
	const char	*last;

	if (!path)
		return (path);
	p = path;
	last = path;
	while (*p)
	{
		if (*p == '/')
			last = p + 1;
		p++;
	}
	return (last);
}

int	is_hidden_file_with_ext(const char *path, const char *extension)
{
	const char	*base;
	size_t		i;

	size_t base_len, ext_len;
	if (!path || !extension)
		return (0);
	base = ft_basename(path);
	if (!base || base[0] != '.')
		return (0);
	base_len = ft_strlen(base);
	ext_len = ft_strlen(extension);
	if (base_len < ext_len)
		return (0);
	i = 0;
	while (i < ext_len && base[base_len - ext_len + i] == extension[i])
		i++;
	return (i == ext_len);
}
