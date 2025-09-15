#ifndef DRAW_H
# define DRAW_H

typedef struct s_image
{
	void				*img_ptr;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_image;

typedef struct s_point_coordinate
{
	int					x;
	int					y;
	int					z;

}						t_point_coordinate;

typedef struct s_line
{
	t_point_coordinate	start;
	t_point_coordinate	end;

}						t_line;

typedef struct s_line_state
{
	int					dx;
	int					dy;
	int					err;
	int					sx;
	int					sy;
}						t_line_state;

void					ft_mlx_pixel_put(t_image *img, int x, int y, int color);
t_line_state			init_line_state(t_point_coordinate start,
							t_point_coordinate end);
void					projection(t_point_coordinate *point);


#endif