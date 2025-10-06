#include "colors.h"
#include "math.h"
#include "render.h"
#include "stdlib.h"

typedef struct s_dda_state
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		i;
	double	t;
	int		color;
}			t_dda_state;

static t_dda_state	init_dda(t_point2d start, t_point2d end)
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

static void	draw_line_dda(t_render *render, t_point2d start, t_point2d end)
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

void	draw_line_bresenham(t_render *render, t_point2d start, t_point2d end)
{
	t_point2d		current_point;
	t_line_state	line_state;
	double			t;

	int e2, total_steps, step, color;
	current_point = start;
	line_state = line_error_calc(start, end);
	if (line_state.dx > line_state.dy)
		total_steps = line_state.dx;
	else
		total_steps = line_state.dy;
	if (total_steps == 0)
		total_steps = 1;
	step = 0;
	while (1)
	{
		t = (double)step / total_steps;
		color = color_blend(start.color, end.color, t); // ← color_lerp değil
		put_pixel(render, current_point.x, current_point.y, color);
		if (current_point.x == end.x && current_point.y == end.y)
			break ;
		e2 = 2 * line_state.err;
		if (e2 >= -line_state.dy)
		{
			line_state.err -= line_state.dy;
			current_point.x += line_state.sx;
		}
		if (e2 <= line_state.dx)
		{
			line_state.err += line_state.dx;
			current_point.y += line_state.sy;
		}
		step++;
	}
}
void	draw_line_hybrid(t_render *render, t_point2d start, t_point2d end)
{
	int dx = abs(end.x - start.x);
	int dy = abs(end.y - start.y);
	int distance = dx + dy;

	if (distance < 50)
		draw_line_dda(render, start, end);
	else
		draw_line_bresenham(render, start, end);
}
