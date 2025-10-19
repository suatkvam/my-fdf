/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:54:40 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_value(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	sign;
	int	res;
	int	val;
	int	i;

	sign = 1;
	res = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		val = get_value(str[i]);
		if (val < 0 || val >= str_base)
			return (-1);
		res = res * str_base + val;
		i++;
	}
	return (res * sign);
}
