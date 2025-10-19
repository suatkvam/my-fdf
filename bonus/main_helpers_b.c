/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 17:57:06 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_map	*parse_map_error(char *map_name)
{
	if (map_name)
		free(map_name);
	return (NULL);
}

char	*extract_map_name(const char *filepath)
{
	const char	*last_slash;
	const char	*dot;
	char		*name;
	int			len;

	last_slash = ft_strrchr(filepath, '/');
	if (last_slash)
		filepath = last_slash + 1;
	dot = ft_strrchr(filepath, '.');
	if (dot)
		len = dot - filepath;
	else
		len = ft_strlen(filepath);
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, filepath, len + 1);
	return (name);
}
