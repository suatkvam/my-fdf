#include "draw.h"
#include "fdf.h"

void	ft_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}
