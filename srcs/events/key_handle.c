#include "fdf.h"

int	handle_key_press(int keycode, t_fdf_data *fdf)
{
	if (keycode == 65307) // ESC tuşu (X11 keycode)
	{
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		exit(0); // programdan çık
	}
	return (0);
}