/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_blend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:47:27 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

int	color_blend(int start_color, int end_color, double t)
{
	t_color	start;
	t_color	end;
	t_color	result;

	if (start_color == -1)
		start_color = 0xFFFFFF;
	if (end_color == -1)
		end_color = 0xFFFFFF;
	if (t < 0.0)
		t = 0.0;
	if (t > 1.0)
		t = 1.0;
	start.r = (start_color >> 16) & 0xFF;
	start.g = (start_color >> 8) & 0xFF;
	start.b = start_color & 0xFF;
	end.r = (end_color >> 16) & 0xFF;
	end.g = (end_color >> 8) & 0xFF;
	end.b = end_color & 0xFF;
	result.r = (int)(start.r + (end.r - start.r) * t);
	result.g = (int)(start.g + (end.g - start.g) * t);
	result.b = (int)(start.b + (end.b - start.b) * t);
	return ((result.r << 16) | (result.g << 8) | result.b);
}
