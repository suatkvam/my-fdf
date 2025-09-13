#ifndef PARS_H
# define PARS_H

# include "get_next_line_bonus.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

# define MAP_ERR_INVALID -1
/* map hatalı: satır uzunlukları tutmuyor veya boş file */
# define MAP_ERR_OPEN -2 /* dosya açılamadı */

typedef struct s_get_map_dimensions
{
	int		fd;
	int		expected_columns;
	int		line_num;
	int		current_columns;
	char	**split_lines;
	char	*line;
}			t_get_map_dimensions;

int			open_file(const char *file_name);
int			get_map_dimensions(const char *file_name);

#endif