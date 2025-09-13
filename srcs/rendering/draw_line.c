#include "draw.h"
#include "fdf.h"

t_line_state	line_error_calc(t_point_coordinate start,
		t_point_coordinate end)
{
	t_line_state	line_state;

	line_state.dx = abs(end.x - start.x); // x2 - x1
	line_state.dy = abs(end.y - start.y); // y2 -y1
	if (start.x < end.x)                // x1 < x2
		line_state.sx = 1;                // sağa git
	else
		line_state.sx = -1; // sola git
	if (start.y < end.y)    // y1 < y2
		line_state.sy = 1;  // aşağı git
	else
		line_state.sy = -1; // yukarı git
	return line_state;
}

void	draw_line(t_fdf_data *fdf, t_line *line)
{
	t_point_coordinate	point;
	t_line_state		line_state;
	int					err;

	point = line->start;
	line_state = line_error_calc(line->start, line->end);
	while (point.x != line->end.x || point.y != line->end.y)
	{
		mlx_pixel_put(fdf->mlx,fdf->win,point.x,point.y, 0xFFFFFF);
		err = line_state.err;
		if(err > -line_state.dx)
		{
			line_state.err -= line_state.dy;
			point.x += line_state.sx;
		}
		if(err < line_state.dy)
		{
			line_state.err += line_state.dx;
			point.y += line_state.sy;
		}
	}
	mlx_pixel_put(fdf->mlx,fdf->win,line->end.x,line->end.y,0xFFFFFF);
}
