/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:17:32 by akivam            #+#    #+#             */
/*   Updated: 2025/06/26 09:17:33 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putnbr_unsigned(unsigned int n, int *len)
{
	if (n >= 10)
		ft_putnbr_unsigned(n / 10, len);
	ft_putchar(((n % 10) + '0'), len);
}
