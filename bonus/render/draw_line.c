/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:53:50 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "math.h"
#include "render.h"
#include "stdlib.h"

void	draw_line_bresenham(t_render *render, t_point2d start, t_point2d end)
{
	t_bresenham_data	data;

	data.current_point = start;
	data.line_state = line_error_calc(start, end);
	if (data.line_state.dx > data.line_state.dy)
		data.total_steps = data.line_state.dx;
	else
		data.total_steps = data.line_state.dy;
	if (data.total_steps == 0)
		data.total_steps = 1;
	data.step = 0;
	bresenham_draw_loop(render, &data, start, end);
}

void	draw_line_hybrid(t_render *render, t_point2d start, t_point2d end)
{
	int	dx;
	int	dy;
	int	distance;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	distance = dx + dy;
	if (distance < 50)
		draw_line_dda(render, start, end);
	else
		draw_line_bresenham(render, start, end);
}
