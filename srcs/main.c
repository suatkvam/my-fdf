#include "draw.h"
#include "fdf.h"
#include "pars.h"
#include "get_next_line.h"
int	main(int argc, char **argv)
{
	t_fdf_data data;

	// 1. ARGÜMAN KONTROLÜ
	if (argc != 2)
		return (ft_putendl_fd("Usage: ./fdf <filename.fdf>", 2), 1);
	// TODO: Burada dosya uzantısının .fdf olduğunu da kontrol edebilirsiniz.
	// if (!check_extension(argv[1], ".fdf")) ...

	// 2. VERİ YAPISINI HAZIRLAMA
	init_data(&data);

	// 3. HARİTAYI OKUMA VE AYRIŞTIRMA (PARSING)
	// TODO: get_map_dimensions'ı width ve height'ı ayrı ayrı
	// alacak şekilde güncellemeniz daha iyi olur.
	// Şimdilik, haritanın geçerli olup olmadığını kontrol edelim.
	if (get_map_dimensions(argv[1]) < 0) // Basit bir geçerlilik kontrolü
		return (1);                     
			// get_map_dimensions zaten hata mesajını basıyor.

	// TODO: Haritanın width ve height'ını 'data' struct'ına doldurun.
	// TODO: Bu width ve height'a göre 'data.map' için malloc ile yer ayırın.
	// TODO: Dosyayı ikinci kez okuyup 'data.map' matrisini doldurun.

	// 4. GRAFİK ORTAMINI HAZIRLAMA
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, data.win_width, data.win_height, "FdF");
	if (!data.win)
		return (1);
	data.img.img_ptr = mlx_new_image(data.mlx, data.win_width, data.win_height);
	data.img.addr = mlx_get_data_addr(data.img.img_ptr,
			&data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	data.img.width = data.win_width;
	data.img.height = data.win_height;

	// 5. EKRANA İLK GÖRÜNTÜYÜ ÇİZDİRME
	render_grid(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img_ptr, 0, 0);

	// 6. OLAYLARI (HOOKS) AYARLAMA VE DÖNGÜYÜ BAŞLATMA
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, handle_key_press, &data);
	mlx_loop(data.mlx);

	return (0);
}