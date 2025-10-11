#include "parser.h"
static const char	*ft_basename(const char *path)
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

static int	has_extension(const char *path, const char *ext)
{
	const char *base;
	size_t base_len;
	size_t ext_len;

	if (!path || !ext)
		return (0);
	base = ft_basename(path);
	if (!base)
		return (0);
	base_len = ft_strlen(base);
	ext_len = ft_strlen(ext);
	if (base_len <= ext_len)
		return (0);
	base += base_len - ext_len;
	while (*base && *ext && *base == *ext)
	{
		base++;
		ext++;
	}
	return (*ext == '\0');
}

int	is_valid_file(const char *path)
{
	if (!path)
		return (0);
	// Support both .fdf and .stl files
	return (has_extension(path, MAP_EXTENSION) || has_extension(path, ".stl"));
}