/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:45:15 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include "get_next_line.h"

void	destroy_render(t_render *render)
{
	if (!render)
		return ;
	if (render->image)
		mlx_destroy_image(render->mlx, render->image);
	if (render->window)
		mlx_destroy_window(render->mlx, render->window);
	if (render->mlx)
	{
		mlx_destroy_display(render->mlx);
		free(render->mlx);
	}
	if (render->map)
		free_map(render->map);
	get_next_line(-1);
	free(render);
}
