#include "fdf.h"

int	close_window(t_fdf_data *fdf)
{
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
}