#include "fdf.h"

void init_data(t_fdf_data *data)
{
    data->mlx = NULL;
    data->win = NULL;
    data->map = NULL;
    data->width = WIN_WIDTH;
    data->height = WIN_HEIGHT;
}