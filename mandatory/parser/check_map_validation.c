/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:55:59 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "printf.h"

static int	validate_all_lines(char **lines, int expected_cols)
{
	int	i;
	int	cols;

	i = 0;
	while (lines[i])
	{
		cols = count_cells(lines[i]);
		if (cols != expected_cols)
		{
			if (cols > expected_cols)
				ft_err_printf("Found wrong line length. Exiting.\n");
			else
				ft_err_printf("Found wrong column length. Exiting.\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

// Satır ve sütun kontrolü
int	check_map_valid(char **lines)
{
	int	expected_cols;

	if (!lines || !lines[0])
	{
		ft_err_printf("Found wrong line length. Exiting.\n");
		return (-1);
	}
	expected_cols = count_cells(lines[0]);
	if (expected_cols == 0)
	{
		ft_err_printf("Found wrong line length. Exiting.\n");
		return (-1);
	}
	return (validate_all_lines(lines, expected_cols));
}
