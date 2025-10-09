#ifndef RENDER_H
# define RENDER_H

# include "parser.h"
# include <mlx.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_TITLE "FDF - 3D Wireframe"

// Projection types
typedef enum e_projection
{
	PROJ_ISOMETRIC = 0,
	PROJ_PERSPECTIVE = 1,
	PROJ_ORTHOGRAPHIC = 2,
	PROJ_TOP_DOWN = 3,
	PROJ_FRONT_VIEW = 4,
	PROJ_SIDE_VIEW = 5,
	PROJ_COUNT = 6
}	t_projection;

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
	t_projection	projection_type;
	float	perspective_distance;
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
t_point2d	project_point_multi(t_point point, t_render *render);
float		calculate_scale(t_map *map);

// Projection functions
t_point2d	project_isometric(t_point point, t_render *render);
t_point2d	project_perspective(t_point point, t_render *render);
t_point2d	project_orthographic(t_point point, t_render *render);
t_point2d	project_top_down(t_point point, t_render *render);
t_point2d	project_front_view(t_point point, t_render *render);
t_point2d	project_side_view(t_point point, t_render *render);
void		cycle_projection(t_render *render);
void		clear_image(t_render *render);

// Main render functions
int			start_render(t_render *render);

// Event handlers
int			handle_key_press(int keycode, t_render *render);
int			handle_mouse_wheel(int button, int x, int y, t_render *render);
int			close_window(t_render *render);

#endif