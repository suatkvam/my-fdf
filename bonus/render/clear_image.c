/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:53:34 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "render.h"
#include "stdlib.h"

void	clear_image(t_render *render)
{
	int	x;
	int	y;

	y = 0;
	while (y < render->window_height)
	{
		x = 0;
		while (x < render->window_width)
		{
			put_pixel(render, x, y, COLOR_BLACK);
			x++;
		}
		y++;
	}
}
