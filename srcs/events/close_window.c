#include "fdf.h"
int	close_window(t_fdf_data *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}