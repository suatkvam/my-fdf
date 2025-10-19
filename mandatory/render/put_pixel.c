/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:45:34 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "stdlib.h"
#include <math.h>

void	put_pixel(t_render *render, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= render->window_width || y < 0
		|| y >= render->window_height)
		return ;
	dst = render->img_data + (y * render->line_length + x
			* (render->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
