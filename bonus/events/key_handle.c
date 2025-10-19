/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:47:58 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdlib.h>

static void	handle_movement_keys(int keycode, t_render *render)
{
	if (keycode == 119)
		render->offset_y -= 20;
	else if (keycode == 115)
		render->offset_y += 20;
	else if (keycode == 97)
		render->offset_x -= 20;
	else if (keycode == 100)
		render->offset_x += 20;
	else if (keycode == 113)
		render->rotation_y -= 0.1;
	else if (keycode == 101)
		render->rotation_y += 0.1;
}

static void	handle_projection_keys(int keycode, t_render *render)
{
	if (keycode == 49)
		render->projection_type = PROJ_ISOMETRIC;
	else if (keycode == 50)
		render->projection_type = PROJ_PERSPECTIVE;
	else if (keycode == 51)
		render->projection_type = PROJ_ORTHOGRAPHIC;
	else if (keycode == 52)
		render->projection_type = PROJ_TOP_DOWN;
	else if (keycode == 53)
		render->projection_type = PROJ_FRONT_VIEW;
	else if (keycode == 54)
		render->projection_type = PROJ_SIDE_VIEW;
	else if (keycode == 112)
		cycle_projection(render);
}

int	handle_key_press(int keycode, t_render *render)
{
	if (keycode == 65307)
	{
		destroy_render(render);
		exit(0);
	}
	handle_movement_keys(keycode, render);
	handle_projection_keys(keycode, render);
	if (keycode != 65307)
		render_map(render);
	return (0);
}
