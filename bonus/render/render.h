/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:54:14 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math3d.h"
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
}					t_projection;

typedef struct s_render
{
	void			*mlx;
	void			*window;
	void			*image;
	char			*img_data;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				window_width;
	int				window_height;
	t_map			*map;
	char			*map_name;
	float			offset_x;
	float			offset_y;
	float			rotation_x;
	float			rotation_y;
	float			zoom_factor;
	t_projection	projection_type;
	float			perspective_distance;
}					t_render;

typedef struct s_point2d
{
	int				x;
	int				y;
	int				color;
}					t_point2d;

typedef struct s_line_state
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
}					t_line_state;

typedef struct s_dda_state
{
	int				dx;
	int				dy;
	int				steps;
	float			x_inc;
	float			y_inc;
	float			x;
	float			y;
	int				i;
	double			t;
	int				color;
}					t_dda_state;

typedef struct s_perspective_data
{
	t_point2d		projected;
	t_3D_vec		rotated_point;
	t_matrix4		rotation_matrix;
	t_3D_vec		original;
	float			scale;
	float			z_depth;
	float			perspective_factor;
}					t_perspective_data;

typedef struct s_orthographic_data
{
	t_point2d		projected;
	t_3D_vec		rotated_point;
	t_matrix4		rotation_matrix;
	t_3D_vec		original;
	float			scale;
}					t_orthographic_data;

typedef struct s_bresenham_data
{
	t_point2d		current_point;
	t_line_state	line_state;
	double			t;
	int				e2;
	int				total_steps;
	int				step;
	int				color;
}					t_bresenham_data;

typedef struct s_projection_var
{
	float			scale;
	float			z_factor;
	float			centered_x;
	float			centered_y;
	float			rotated_x;
	float			rotated_y;
}					t_projection_vars;

// Window functions
t_render			*init_render(t_map *map, char *map_name);
void				destroy_render(t_render *render);
t_render			*create_render_struct(t_map *map, char *map_name);
int					init_mlx_window(t_render *render, char *map_name);
int					init_mlx_image(t_render *render);

// Drawing functions
void				render_map(t_render *render);
void				render_row(t_render *render, int y);
void				render_point_connections(t_render *render, int x, int y);
void				draw_line_hybrid(t_render *render, t_point2d start,
						t_point2d end);
void				draw_line_bresenham(t_render *render, t_point2d start,
						t_point2d end);
void				bresenham_draw_loop(t_render *render,
						t_bresenham_data *data, t_point2d start, t_point2d end);
void				put_pixel(t_render *render, int x, int y, int color);
t_dda_state			init_dda(t_point2d start, t_point2d end);
void				draw_line_dda(t_render *render, t_point2d start,
						t_point2d end);
t_line_state		line_error_calc(t_point2d start, t_point2d end);
t_point2d			project_point(t_point point);
t_point2d			project_point_scaled(t_point point, t_map *map);
t_point2d			project_point_interactive(t_point point, t_render *render);
t_point2d			project_point_multi(t_point point, t_render *render);
float				calculate_scale(t_map *map);
int					get_max_dimension(t_map *map);
float				calculate_z_factor(t_map *map);
int					set_point_color(int original_color);

// Projection functions
t_point2d			project_isometric(t_point point, t_render *render);
t_point2d			project_perspective(t_point point, t_render *render);
t_point2d			project_orthographic(t_point point, t_render *render);
t_point2d			project_top_down(t_point point, t_render *render);
t_point2d			project_front_view(t_point point, t_render *render);
t_point2d			project_side_view(t_point point, t_render *render);
void				cycle_projection(t_render *render);
void				clear_image(t_render *render);

// Main render functions
int					start_render(t_render *render, char *map_name);

// Event handlers
int					handle_key_press(int keycode, t_render *render);
int					handle_mouse_wheel(int button, int x, int y,
						t_render *render);
int					close_window(t_render *render);

#endif
