#include "fdf.h"
#include "draw.h"


void render_grid(t_fdf_data *fdf, t_point_coordinate *coords, int width, int height)
{
    int x, y;
    t_line line;

    // yatay çizgiler
    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width - 1)
        {
            line.start.x = coords[y * width + x].x * fdf->zoom + fdf->offset_x;
            line.start.y = coords[y * width + x].y * fdf->zoom + fdf->offset_y;

            line.end.x = coords[y * width + (x + 1)].x * fdf->zoom + fdf->offset_x;
            line.end.y = coords[y * width + (x + 1)].y * fdf->zoom + fdf->offset_y;

            draw_line(fdf, &line);
            x++;
        }
        y++;
    }

    // dikey çizgiler
    x = 0;
    while (x < width)
    {
        y = 0;
        while (y < height - 1)
        {
            line.start.x = coords[y * width + x].x * fdf->zoom + fdf->offset_x;
            line.start.y = coords[y * width + x].y * fdf->zoom + fdf->offset_y;

            line.end.x = coords[(y + 1) * width + x].x * fdf->zoom + fdf->offset_x;
            line.end.y = coords[(y + 1) * width + x].y * fdf->zoom + fdf->offset_y;

            draw_line(fdf, &line);
            y++;
        }
        x++;
    }

    // Çizilen image'i pencereye bastır
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img_ptr, 0, 0);
}
