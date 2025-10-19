/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/18 17:59:06 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "render.h"
#include "../colors/colors.h"

int	expose_handler(t_render *render)
{
	render_map(render);
	return (0);
}

int	start_render(t_render *render, char *map_name)
{
	if (!render)
		return (1);
	ft_printf(ANSI_COLOR_YELLOW);
	ft_printf("[%s]", map_name);
	ft_printf(ANSI_COLOR_RESET " Rendering initial map...\n");
	render_map(render);
	ft_printf(ANSI_COLOR_GREEN);
	ft_printf("[%s]", map_name);
	ft_printf(ANSI_COLOR_RESET " Map rendered, setting up event handlers...\n");
	mlx_key_hook(render->window, handle_key_press, render);
	mlx_hook(render->window, 17, 0, close_window, render);
	mlx_mouse_hook(render->window, handle_mouse_wheel, render);
	mlx_expose_hook(render->window, expose_handler, render);
	ft_printf(ANSI_COLOR_BLUE);
	ft_printf("[%s]", map_name);
	ft_printf(ANSI_COLOR_RESET " MLX loop started\n");
	mlx_loop(render->mlx);
	return (0);
}
