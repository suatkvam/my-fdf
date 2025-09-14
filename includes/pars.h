#ifndef PARS_H
# define PARS_H

# include "draw.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

# define c ".fdf"
# define MAP_ERR_INVALID -1
/* map hatalı: satır uzunlukları tutmuyor veya boş file */
# define MAP_ERR_OPEN -2 /* dosya açılamadı */

typedef struct s_get_map_dimensions
{
	int					fd;
	int					expected_columns;
	int					line_num;
	int					current_columns;
	char				**split_lines;
	char				*line;
}						t_get_map_dimensions;

typedef struct s_get_coordinates
{
    int                 fd;
    int                 width;
    int                 height;
    t_point_coordinate  *coordinates;
    int                 row;
    int                 index;
    char                *line;
} t_get_coordinates;

const char				*ft_basename(const char *path);
int						is_hidden_file_with_ext(const char *path,
							const char *extension);

int						open_file(const char *file_name);
int						get_map_dimensions(const char *file_name);

t_point_coordinate		*get_coordinates(const char *file_name,
							int *total_cells);
#endif