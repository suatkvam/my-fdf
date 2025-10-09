#include "render.h"
#include <stdlib.h>

t_render	*init_render(t_map *map)
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
	render->offset_x = 0.0;
	render->offset_y = 0.0;
	render->rotation_x = 0.0;
	render->rotation_y = 0.0;
	render->zoom_factor = 1.0;
	render->projection_type = PROJ_ISOMETRIC;
	render->perspective_distance = 1000.0;
	render->window = mlx_new_window(render->mlx, render->window_width,
			render->window_height, WINDOW_TITLE);
	if (!render->window)
	{
		free(render);
		return (NULL);
	}
	render->image = mlx_new_image(render->mlx, render->window_width,
			render->window_height);
	if (!render->image)
	{
		mlx_destroy_window(render->mlx, render->window);
		free(render);
		return (NULL);
	}
	render->img_data = mlx_get_data_addr(render->image, &render->bits_per_pixel,
			&render->line_length, &render->endian);
	return (render);
}
