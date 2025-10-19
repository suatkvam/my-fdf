/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:53:52 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>

t_render	*create_render_struct(t_map *map, char *map_name)
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
	render->map_name = map_name;
	render->offset_x = 0.0;
	render->offset_y = 0.0;
	render->rotation_x = 0.0;
	render->rotation_y = 0.0;
	render->zoom_factor = 1.0;
	render->projection_type = PROJ_ISOMETRIC;
	render->perspective_distance = 1000.0;
	return (render);
}

int	init_mlx_window(t_render *render, char *map_name)
{
	char	*title;
	char	*prefix;
	int		title_len;

	prefix = "FDF - ";
	title_len = ft_strlen(prefix) + ft_strlen(map_name) + 1;
	title = malloc(title_len);
	if (!title)
		return (-1);
	ft_strlcpy(title, prefix, title_len);
	ft_strlcat(title, map_name, title_len);
	render->window = mlx_new_window(render->mlx, render->window_width,
			render->window_height, title);
	free(title);
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

t_render	*init_render(t_map *map, char *map_name)
{
	t_render	*render;

	render = create_render_struct(map, map_name);
	if (!render)
		return (NULL);
	if (init_mlx_window(render, map_name) != 0)
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
