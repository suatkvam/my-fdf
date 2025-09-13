#include "fdf.h"

int	handle_key_press(int keycode, t_fdf_data *mlx)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}