#include "render.h"
#include "stdlib.h"
#include <math.h>

void	put_pixel(t_render *render, int x, int y, int color)
{
	char *dst;
	if (x < 0 || x >= render->window_width || y < 0
		|| y >= render->window_height)
		return ;
	dst = render->img_data + (y * render->line_length + x
			* (render->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}