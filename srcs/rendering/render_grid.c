/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by akivam            #+#    #+#             */
/*   Updated: 2025/09/16 14:32:49 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "fdf.h"
#include "pars.h"

/*
** Transforms coordinates and draws a line between two points.
** Applies centering, zoom, projection, and offset in correct order.
*/

static void	draw_projected_line(t_fdf_data *fdf, t_point_coordinate start,
		t_point_coordinate end, t_map_data map)
{
	t_line	line;

	start.x -= map.width / 2;
	start.y -= map.height / 2;
	end.x -= map.width / 2;
	end.y -= map.height / 2;
	start.x *= fdf->zoom;
	start.y *= fdf->zoom;
	start.z *= fdf->zoom;
	end.x *= fdf->zoom;
	end.y *= fdf->zoom;
	end.z *= fdf->zoom;
	projection(&start);
	projection(&end);
	line.start.x = start.x + fdf->offset_x;
	line.start.y = start.y + fdf->offset_y;
	line.end.x = end.x + fdf->offset_x;
	line.end.y = end.y + fdf->offset_y;
	draw_line(fdf, &line);
}

/*
** Draws horizontal lines connecting adjacent points in each row.
*/

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
			draw_projected_line(fdf, coords[y * map.width + x],
				coords[y * map.width + (x + 1)], map);
			x++;
		}
		y++;
	}
}

/*
** Draws vertical lines connecting adjacent points in each column.
*/

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
			draw_projected_line(fdf, coords[y * map.width + x],
				coords[(y + 1) * map.width + x], map);
			y++;
		}
		x++;
	}
}

/*
** Main rendering function that draws the wireframe grid.
** Renders horizontal and vertical lines, then displays the result.
*/

void	render_grid(t_fdf_data *fdf, t_point_coordinate *coordinates,
		t_map_data map)
{
	draw_horizontal_lines(fdf, coordinates, map);
	draw_vertical_lines(fdf, coordinates, map);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
}