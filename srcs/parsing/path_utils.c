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

int	is_valid_map_file(const char *path)
{
	const char *base;
	const char *extension = MAP_EXTENSION;
	size_t base_len;
	size_t ext_len;

	if (!path)
		return (0);

	base = ft_basename(path);
	if (!base)
		return (0);

	base_len = ft_strlen(base);
	ext_len = ft_strlen(extension);

	// Kural 2: Dosya adı uzantıdan uzun olmalı mı?
	if (base_len <= ext_len)
		return (0);

	// Kural 1: Dosya '.fdf' ile bitiyor mu?
	// Dosya adının son 'ext_len' karakterini uzantı ile karşılaştır.
	base += base_len - ext_len;
	while (*base && *extension && *base == *extension)
	{
		base++;
		extension++;
	}

	if (*extension == '\0')
		return (1); // Eşleşme tamam.

	return (0); // Eşleşme yok.
}