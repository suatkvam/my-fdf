#ifndef FDF_H
# define FDF_H

# include "draw.h"
# include "mlx.h"
# include "pars.h"
# include <fcntl.h>
# include <math.h>

# define MAP_EXTENSION ".fdf"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
typedef struct s_fdf_data
{
	// MLX ile ilgili her şey
	void	*mlx;
	void	*win;
	t_image	img;

	// harita ile ilgli her şey
	int		**map;
	int		width;
	int		height;
	int		win_width;
	int		win_height;

	// kamera/ görünüm ile ilgili herşey;
	int		zoom;
	int		offset_x;
	int		offset_y;
}			t_fdf_data;
void		init_data(t_fdf_data *data);
int			handle_key_press(int keycode, t_fdf_data *mlx);
int			close_window(t_fdf_data *mlx);

int			is_valid_map_file(const char *path);

void		draw_line(t_fdf_data *fdf, t_line *line);
void		render_grid(t_fdf_data *data);

#endif