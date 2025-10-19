/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:54:10 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render_point_connections(t_render *render, int x, int y)
{
	t_point		current_point;
	t_point2d	current_2d;
	t_point2d	right_2d;
	t_point2d	down_2d;

	current_point = render->map->grid[y][x];
	current_2d = project_point_multi(current_point, render);
	if (x < render->map->width - 1)
	{
		right_2d = project_point_multi(render->map->grid[y][x + 1],
				render);
		draw_line_hybrid(render, current_2d, right_2d);
	}
	if (y < render->map->height - 1)
	{
		down_2d = project_point_multi(render->map->grid[y + 1][x],
				render);
		draw_line_hybrid(render, current_2d, down_2d);
	}
}

void	render_row(t_render *render, int y)
{
	int	x;

	x = 0;
	while (x < render->map->width)
	{
		render_point_connections(render, x, y);
		x++;
	}
}

void	render_map(t_render *render)
{
	int	y;

	if (!render || !render->map)
		return ;
	clear_image(render);
	y = 0;
	while (y < render->map->height)
	{
		render_row(render, y);
		y++;
	}
	mlx_put_image_to_window(render->mlx, render->window, render->image, 0, 0);
}
