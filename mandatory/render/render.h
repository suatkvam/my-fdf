/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:43:19 by akivam            #+#    #+#             */
/*   Updated: 2025/10/16 18:45:42 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "parser.h"
# include <mlx.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_TITLE "FDF - 3D Wireframe"

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
}					t_render;

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

// Window functions
t_render			*init_render(t_map *map);
void				destroy_render(t_render *render);
t_render			*create_render_struct(t_map *map);
int					init_mlx_window(t_render *render);
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
t_point2d			project_point(t_point point, t_map *map);
t_point2d			project_point_scaled(t_point point, t_map *map);
float				calculate_scale(t_map *map);
int					get_max_dimension(t_map *map);
float				calculate_z_factor(t_map *map);
t_point2d			calculate_projection_coords(t_point point, float scale,
						float z_factor, t_map *map);
int					set_point_color(int original_color);
void				clear_image(t_render *render);

// Main render functions
int					start_render(t_render *render);

// Event handlers
int					handle_key_press(int keycode, t_render *render);
int					close_window(t_render *render);

#endif
