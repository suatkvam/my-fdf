/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:48:19 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	handle_mouse_wheel(int button, int x, int y, t_render *render)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		render->zoom_factor *= 1.1;
		if (render->zoom_factor > 5.0)
			render->zoom_factor = 5.0;
	}
	else if (button == 5)
	{
		render->zoom_factor *= 0.9;
		if (render->zoom_factor < 0.1)
			render->zoom_factor = 0.1;
	}
	render_map(render);
	return (0);
}
