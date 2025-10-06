#include "render.h"
#include <stdlib.h>

int	handle_key_press(int keycode, t_render *render)
{
	if (keycode == 65307) // ESC tuşu (X11 keycode)
	{
		destroy_render(render);
		exit(0);
	}
	return (0);
}