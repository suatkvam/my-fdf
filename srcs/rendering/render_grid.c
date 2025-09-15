#include "draw.h"
#include "fdf.h"
#include "pars.h"

static void	draw_projected_line(t_fdf_data *fdf, t_point_coordinate start,
		t_point_coordinate end, t_map_data map)
{
	t_line	line;

	start.x -= map.width / 2;
	start.y -= map.height / 2;
	end.x -= map.width / 2;
	end.y -= map.height / 2;
	projection(&start); // Bu fonksiyonun var olması gerekiyor
	projection(&end);
	line.start.x = start.x * fdf->zoom + fdf->offset_x;
	line.start.y = start.y * fdf->zoom + fdf->offset_y;
	line.end.x = end.x * fdf->zoom + fdf->offset_x;
	line.end.y = end.y * fdf->zoom + fdf->offset_y;
	draw_line(fdf, &line);
}
static void	draw_horizontal_lines(t_fdf_data *fdf,
		t_point_coordinate *coords, t_map_data map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width - 1)
		{
			// draw_projected_line'a 'map' struct'ını da gönderiyoruz
			draw_projected_line(fdf, coords[y * map.width + x], coords[y
				* map.width + (x + 1)], map);
			x++;
		}
		y++;
	}
}
static void	draw_vertical_lines(t_fdf_data *fdf, t_point_coordinate *coords,
		t_map_data map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map.width)
	{
		y = 0;
		while (y < map.height - 1)
		{
			// draw_projected_line'a 'map' struct'ını da gönderiyoruz
			draw_projected_line(fdf, coords[y * map.width + x], coords[(y + 1)
				* map.width + x], map);
			y++;
		}
		x++;
	}
}

void	render_grid(t_fdf_data *fdf, t_point_coordinate *coordinates, t_map_data map)
{
	draw_horizontal_lines(fdf, coordinates, map);
	draw_vertical_lines(fdf, coordinates, map);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
}