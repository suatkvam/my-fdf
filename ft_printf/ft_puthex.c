/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:17:13 by akivam            #+#    #+#             */
/*   Updated: 2025/06/26 09:26:32 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_puthex(unsigned int number, int *len, char *base)
{
	if (number >= 16)
	{
		ft_puthex(number / 16, len, base);
		ft_putchar(base[number % 16], len);
	}
	else
		ft_putchar(base[number % 16], len);
}
