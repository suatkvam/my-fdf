/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:52:58 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_valid_file(const char *path)
{
	const char	*base;
	const char	*extension;
	size_t		base_len;
	size_t		ext_len;

	extension = MAP_EXTENSION;
	if (!path)
		return (0);
	base = ft_basename(path);
	if (!base)
		return (0);
	base_len = ft_strlen(base);
	ext_len = ft_strlen(extension);
	if (base_len <= ext_len)
		return (0);
	base += base_len - ext_len;
	while (*base && *extension && *base == *extension)
	{
		base++;
		extension++;
	}
	if (*extension == '\0')
		return (1);
	return (0);
}
