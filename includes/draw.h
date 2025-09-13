#ifndef DRAW_H
# define DRAW_H

# include "fdf.h"

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

t_line_state			init_line_state(t_point_coordinate start,
							t_point_coordinate end);
void					draw_line(t_fdf_data *fdf, t_line *line);

#endif