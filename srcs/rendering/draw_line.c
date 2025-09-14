#include "draw.h"
#include "fdf.h"

t_line_state	line_error_calc(t_point_coordinate start,
		t_point_coordinate end)
{
	t_line_state	line_state;

	line_state.dx = abs(end.x - start.x); // x2 - x1
	line_state.dy = abs(end.y - start.y); // y2 -y1
	if (start.x < end.x)                  // x1 < x2
		line_state.sx = 1;                // sağa git
	else
		line_state.sx = -1; // sola git
	if (start.y < end.y)    // y1 < y2
		line_state.sy = 1;  // aşağı git
	else
		line_state.sy = -1; // yukarı git
	line_state.err = line_state.dx - line_state.dy;
	return (line_state);
}

void	draw_line(t_fdf_data *fdf, t_line *line)
{
	t_point_coordinate	current_point;
	t_line_state		line_state;
	int					e2;

	current_point = line->start;
	line_state = line_error_calc(line->start, line->end);
	while (1)
	{
		ft_mlx_pixel_put(&fdf->img, current_point.x, current_point.y,
			0x00FFFFFF);// todo: color.h eklenecek unutma
		if (current_point.x == line->end.x && current_point.y == line->end.y)
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
	}
}
