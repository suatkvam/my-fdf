#include "fdf.h"


void	render_grid(t_fdf_data *data)
{
	// TODO: while döngüleri ile data->map'i gez,
	// her noktayı project() ile 2D'ye çevir ve
	// draw_line() ile çiz.

	// Şimdilik bir test çizgisi çizelim:
	t_line test_line;
	test_line.start.x = 100;
	test_line.start.y = 100;
	test_line.end.x = 500;
	test_line.end.y = 500;
	draw_line(data, &test_line);
}