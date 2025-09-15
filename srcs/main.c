#include "fdf.h"   // Projenizin ana header'ı
#include <stdio.h> // printf kullanmak için (isteğe bağlı, hata ayıklama için)

int	main(int argc, char **argv)
{
	t_fdf_data fdf;
	t_map_data map;
	t_point_coordinate *coords;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map_file.fdf>", 2);
		return (1);
	}

	// 1. ADIM: HARİTAYI PARSE ET
	map = get_map_dimensions(argv[1]);
	if (map.width <= 0 || map.height <= 0)
	{
		ft_putendl_fd("Error: Invalid map file.", 2);
		return (1);
	}
	coords = get_coordinates(argv[1], map);
	if (!coords)
	{
		ft_putendl_fd("Error: Failed to load map coordinates.", 2);
		return (1);
	}

	// 2. ADIM: MLX'İ BAŞLAT
	fdf.mlx = mlx_init();
	if (!fdf.mlx)
		return (ft_putendl_fd("Error: mlx_init() failed.", 2), free(coords), 1);
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "akivam's FdF");
	if (!fdf.win)
		return (ft_putendl_fd("Error: mlx_new_window() failed.", 2),
			free(coords), 1);

	// 3. ADIM: ÜZERİNE ÇİZİM YAPILACAK IMAGE'I OLUŞTUR
	fdf.img.img_ptr = mlx_new_image(fdf.mlx, 1920, 1080);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img_ptr, &fdf.img.bits_per_pixel,
			&fdf.img.line_length, &fdf.img.endian);
	fdf.img.width = 1920;
	fdf.img.height = 1080;

	// 4. ADIM: GÖRÜNÜM AYARLARINI (ZOOM, OFFSET) YAP
	fdf.zoom = 40;
	fdf.offset_x = 1920 / 2; // Haritayı biraz sola ve yukarıya ortala
	fdf.offset_y = 1080 / 3;

	// 5. ADIM: EKRANA ÇİZDİR
	render_grid(&fdf, coords,map);

	// 6. ADIM: OLAYLARI YAKALAMAK İÇİN HOOK'LARI AYARLA
	mlx_hook(fdf.win, 2, 1L << 0, handle_key_press, &fdf);
	// Klavye tuşuna basma
	mlx_hook(fdf.win, 17, 0, close_window, &fdf); // Pencereyi kapatma

	// 7. ADIM: PENCEREYİ AÇIK TUT VE OLAYLARI DİNLE
	mlx_loop(fdf.mlx);

	// mlx_loop sonsuz bir döngü olduğu için bu kısıma genellikle ulaşılmaz.
	// Temizlik 'close_window' ve 'handle_key_press' içinde yapılır.
	free(coords);
	return (0);
}