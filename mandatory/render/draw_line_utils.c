/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:45:17 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "math.h"
#include "render.h"
#include "stdlib.h"

t_dda_state	init_dda(t_point2d start, t_point2d end)
{
	t_dda_state	dda;

	dda.dx = end.x - start.x;
	dda.dy = end.y - start.y;
	if (abs(dda.dx) > abs(dda.dy))
		dda.steps = abs(dda.dx);
	else
		dda.steps = abs(dda.dy);
	if (dda.steps == 0)
		dda.steps = 1;
	dda.x_inc = (float)dda.dx / dda.steps;
	dda.y_inc = (float)dda.dy / dda.steps;
	dda.x = start.x;
	dda.y = start.y;
	dda.i = 0;
	return (dda);
}

void	draw_line_dda(t_render *render, t_point2d start, t_point2d end)
{
	t_dda_state	dda;

	dda = init_dda(start, end);
	if (dda.steps == 0)
	{
		put_pixel(render, start.x, start.y, start.color);
		return ;
	}
	while (dda.i <= dda.steps)
	{
		dda.t = (double)dda.i / dda.steps;
		dda.color = color_blend(start.color, end.color, dda.t);
		put_pixel(render, (int)(dda.x + 0.5), (int)(dda.y + 0.5), dda.color);
		dda.x += dda.x_inc;
		dda.y += dda.y_inc;
		dda.i++;
	}
}

t_line_state	line_error_calc(t_point2d start, t_point2d end)
{
	t_line_state	line_state;

	line_state.dx = abs(end.x - start.x);
	line_state.dy = abs(end.y - start.y);
	if (start.x < end.x)
		line_state.sx = 1;
	else
		line_state.sx = -1;
	if (start.y < end.y)
		line_state.sy = 1;
	else
		line_state.sy = -1;
	line_state.err = line_state.dx - line_state.dy;
	return (line_state);
}

void	bresenham_draw_loop(t_render *render, t_bresenham_data *data,
		t_point2d start, t_point2d end)
{
	while (1)
	{
		data->t = (double)data->step / data->total_steps;
		data->color = color_blend(start.color, end.color, data->t);
		put_pixel(render, data->current_point.x, data->current_point.y,
			data->color);
		if (data->current_point.x == end.x && data->current_point.y == end.y)
			break ;
		data->e2 = 2 * data->line_state.err;
		if (data->e2 >= -data->line_state.dy)
		{
			data->line_state.err -= data->line_state.dy;
			data->current_point.x += data->line_state.sx;
		}
		if (data->e2 <= data->line_state.dx)
		{
			data->line_state.err += data->line_state.dx;
			data->current_point.y += data->line_state.sy;
		}
		data->step++;
	}
}
