/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:18:10 by akivam            #+#    #+#             */
/*   Updated: 2025/06/26 09:54:58 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	ft_putstr(char *s, int *len)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		*len += 6;
		return ;
	}
	write(1, s, ft_strlen(s));
	*len += ft_strlen(s);
}
