/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:45:22 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>

t_render	*create_render_struct(t_map *map)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (NULL);
	render->mlx = mlx_init();
	if (!render->mlx)
	{
		free(render);
		return (NULL);
	}
	render->window_width = WINDOW_WIDTH;
	render->window_height = WINDOW_HEIGHT;
	render->map = map;
	return (render);
}

int	init_mlx_window(t_render *render)
{
	render->window = mlx_new_window(render->mlx, render->window_width,
			render->window_height, WINDOW_TITLE);
	if (!render->window)
		return (-1);
	return (0);
}

int	init_mlx_image(t_render *render)
{
	render->image = mlx_new_image(render->mlx, render->window_width,
			render->window_height);
	if (!render->image)
		return (-1);
	render->img_data = mlx_get_data_addr(render->image, &render->bits_per_pixel,
			&render->line_length, &render->endian);
	return (0);
}

t_render	*init_render(t_map *map)
{
	t_render	*render;

	render = create_render_struct(map);
	if (!render)
		return (NULL);
	if (init_mlx_window(render) != 0)
	{
		free(render);
		return (NULL);
	}
	if (init_mlx_image(render) != 0)
	{
		mlx_destroy_window(render->mlx, render->window);
		free(render);
		return (NULL);
	}
	return (render);
}
