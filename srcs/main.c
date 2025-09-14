#include "draw.h"
#include "fdf.h"
#include "libft.h"
#include "pars.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int total_size;
	t_point_coordinate *coords;
	int width, height;
	t_fdf_data fdf;

	if (argc != 2)
		return (1);
	if (!is_valid_map_file(argv[1]))
	{
		ft_putendl_fd("Hata: Harita dosyasi '.fdf' uzantili olmalidir.", 2);
		return (1);
	}

	// Harita boyutlarını al
	total_size = get_map_dimensions(argv[1]);
	if (total_size < 0)
		return (1);
	width = total_size / 2;  // satır sayısı
	height = total_size / 2; // sütun sayısı

	// Koordinatları oku
	coords = get_coordinates(argv[1], &total_size);
	if (!coords)
	{
		ft_putendl_fd("Hata: Koordinatlar alınamadı.", 2);
		return (1);
	}

	printf("Toplam hücre sayısı: %d\n", total_size);
	printf("Width: %d, Height: %d\n", width, height);

	// MLX başlat
	fdf.mlx = mlx_init();
	if (!fdf.mlx)
		return (ft_putendl_fd("Hata: MLX başlatılamadı.", 2), free(coords), 1);
	fdf.win = mlx_new_window(fdf.mlx, 800, 600, "FDF");
	if (!fdf.win)
		return (ft_putendl_fd("Hata: Pencere açılamadı.", 2), free(coords), 1);

	// Image oluştur
	fdf.img.img_ptr = mlx_new_image(fdf.mlx, 800, 600);
	if (!fdf.img.img_ptr)
		return (ft_putendl_fd("Hata: Image oluşturulamadı.", 2), free(coords), 1);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img_ptr,
	                                 &fdf.img.bits_per_pixel,
	                                 &fdf.img.line_length,
	                                 &fdf.img.endian);
	fdf.img.width = 800;
	fdf.img.height = 600;

	// Kamera ve görüntü parametrelerini ayarla
	fdf.zoom = 20;
	fdf.offset_x = 400;
	fdf.offset_y = 300;

	// Grid çiz
	render_grid(&fdf, coords, width, height);

	// Oluşan resmi pencereye koy
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img_ptr, 0, 0);

	// ESC tuşu ve pencere kapatma olayları için hook
	mlx_hook(fdf.win, 2, 1L<<0, handle_key_press, &fdf); // KeyPress
	mlx_hook(fdf.win, 17, 0, close_window, &fdf);        // DestroyNotify

	// Döngü başlat
	mlx_loop(fdf.mlx);

	free(coords);
	return (0);
}
