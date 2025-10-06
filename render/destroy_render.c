#include "render.h"

void destroy_render(t_render *render)
{
    if (!render)
        return;
    if (render->image)
        mlx_destroy_image(render->mlx, render->image);
    if (render->window)
        mlx_destroy_window(render->mlx, render->window);
    if (render->mlx)
    {
        mlx_destroy_display(render->mlx);
        free(render->mlx);
    }
    free(render);
}