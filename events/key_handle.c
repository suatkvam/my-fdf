#include "render.h"
#include <stdlib.h>

int	handle_key_press(int keycode, t_render *render)
{
	if (keycode == 65307) // ESC tuşu (X11 keycode)
	{
		destroy_render(render);
		exit(0);
	}
	// WASD for translation
	else if (keycode == 119) // W - Up
		render->offset_y -= 20;
	else if (keycode == 115) // S - Down
		render->offset_y += 20;
	else if (keycode == 97)  // A - Left
		render->offset_x -= 20;
	else if (keycode == 100) // D - Right
		render->offset_x += 20;
	// QE for rotation
	else if (keycode == 113) // Q - Rotate left
		render->rotation_y -= 0.1;
	else if (keycode == 101) // E - Rotate right
		render->rotation_y += 0.1;
		
	// Re-render after any change
	if (keycode != 65307)
		render_map(render);
		
	return (0);
}