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
	// Number keys 1-6 map directly to projection types
	// '1' -> Isometric, '2' -> Perspective, '3' -> Orthographic
	// '4' -> Top-Down, '5' -> Front View, '6' -> Side View
	else if (keycode == 49) // '1'
		render->projection_type = PROJ_ISOMETRIC;
	else if (keycode == 50) // '2'
		render->projection_type = PROJ_PERSPECTIVE;
	else if (keycode == 51) // '3'
		render->projection_type = PROJ_ORTHOGRAPHIC;
	else if (keycode == 52) // '4'
		render->projection_type = PROJ_TOP_DOWN;
	else if (keycode == 53) // '5'
		render->projection_type = PROJ_FRONT_VIEW;
	else if (keycode == 54) // '6'
		render->projection_type = PROJ_SIDE_VIEW;
	// P for projection cycle (keeps backwards compatibility)
	else if (keycode == 112) // P - Cycle projection
		cycle_projection(render);
		
	// Re-render after any change
	if (keycode != 65307)
		render_map(render);
		
	return (0);
}