#include "draw.h"
#include "fdf.h"
#include "pars.h"

int	main(int argc, char **argv)
{
	t_fdf_data	mlx;
	int			map_size;

	t_line line; // direkt struct
	// Argüman kontrolü
	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	// Map boyutunu al
	map_size = get_map_dimensions(argv[1]);
	if (map_size == -2)
	{
		printf("Error: could not open file %s\n", argv[1]);
		return (1);
	}
	else if (map_size == -1)
	{
		printf("Error: inconsistent map dimensions in %s\n", argv[1]);
		return (1);
	}
	else
		printf("Map size: %d\n", map_size);
	// MiniLibX başlat
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (1);
	mlx.win = mlx_new_window(mlx.mlx, 1000, 1000, "Draw Line Example");
	if (!mlx.win)
		return (1);
	// Çizilecek satırın koordinatları
	line.start.x = 30;
	line.start.y = 50;
	line.start.z = 0;
	line.end.x = 500;
	line.end.y = 60;
	line.end.z = 0;
	// draw_line fonksiyonuna direkt &line veriyoruz
	draw_line(&mlx, &line);
	// Olayları yakala
	mlx_key_hook(mlx.win, handle_key_press, &mlx);
	mlx_hook(mlx.win, 17, 0, close_window, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
