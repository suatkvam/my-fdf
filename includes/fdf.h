#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
#include <stdlib.h>

typedef struct s_fdf_data
{
	// MLX ile ilgili her şey
	void	*mlx;
	void	*win;

	// harita ile ilgli her şey
	int		**map;
	int		width;
	int		height;

	// kamera/ görünüm ile ilgili herşey;
	int		zoom;
	int		offset_x;
	int		offset_y;
}			t_fdf_data;
int			close_window(t_fdf_data *mlx);
int			handle_key_press(int keycode, t_fdf_data *mlx);
#endif