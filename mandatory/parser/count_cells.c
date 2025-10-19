/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cells.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:56:03 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
		|| c == '\v');
}

int	count_cells(const char *line)
{
	int	count;
	int	i;
	int	in_cell;

	count = 0;
	i = 0;
	in_cell = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && !in_cell)
		{
			in_cell = 1;
			count++;
		}
		else if (ft_isspace(line[i]))
			in_cell = 0;
		i++;
	}
	return (count);
}
