/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by akivam            #+#    #+#             */
/*   Updated: 2025/09/16 14:32:49 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "fdf.h"

/*
** Safely puts a pixel to the image at given coordinates with given color.
** Checks boundaries to prevent segmentation faults.
*/

void	ft_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}
