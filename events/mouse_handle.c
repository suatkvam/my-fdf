#include "render.h"

int	handle_mouse_wheel(int button, int x, int y, t_render *render)
{
	(void)x;  // Unused parameters
	(void)y;
	
	if (button == 4) // Mouse wheel up (zoom in)
	{
		render->zoom_factor *= 1.1;
		if (render->zoom_factor > 5.0) // Max zoom limit
			render->zoom_factor = 5.0;
	}
	else if (button == 5) // Mouse wheel down (zoom out)
	{
		render->zoom_factor *= 0.9;
		if (render->zoom_factor < 0.1) // Min zoom limit
			render->zoom_factor = 0.1;
	}
	
	// Re-render after zoom change
	render_map(render);
	
	return (0);
}