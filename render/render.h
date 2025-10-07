#ifndef RENDER_H
# define RENDER_H

# include "parser.h"
# include <mlx.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_TITLE "FDF - 3D Wireframe"

typedef struct s_render
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		window_width;
	int		window_height;
	t_map	*map;
	float	offset_x;
	float	offset_y;
	float	rotation_x;
	float	rotation_y;
	float	zoom_factor;
}			t_render;

typedef struct s_point2d
{
	int		x;
	int		y;
	int		color;
}			t_point2d;

typedef struct s_line_state
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}			t_line_state;

// Window functions
t_render	*init_render(t_map *map);
void		destroy_render(t_render *render);

// Drawing functions
void		render_map(t_render *render);
void		draw_line_hybrid(t_render *render, t_point2d start, t_point2d end);
void		put_pixel(t_render *render, int x, int y, int color);
t_point2d	project_point(t_point point);
t_point2d	project_point_scaled(t_point point, t_map *map);
t_point2d	project_point_interactive(t_point point, t_render *render);
float		calculate_scale(t_map *map);
void		clear_image(t_render *render);

// Main render functions
int			start_render(t_render *render);

// Event handlers
int			handle_key_press(int keycode, t_render *render);
int			close_window(t_render *render);

#endif