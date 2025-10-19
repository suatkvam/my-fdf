/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:45:53 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "render.h"
#include "colors.h"

int	start_render(t_render *render)
{
	if (!render)
		return (1);
	ft_printf(ANSI_CYAN "Rendering initial map..." ANSI_RESET "\n");
	render_map(render);
	ft_printf(ANSI_GREEN "Map rendered, setting up event handlers..."\
		ANSI_RESET "\n");
	mlx_key_hook(render->window, handle_key_press, render);
	mlx_hook(render->window, 17, 0, close_window, render);
	ft_printf(ANSI_MAGENTA "Starting MLX loop..." ANSI_RESET "\n");
	mlx_loop(render->mlx);
	return (0);
}
