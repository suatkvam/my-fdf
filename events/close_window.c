#include "render.h"
#include <stdlib.h>

int	close_window(t_render *render)
{
	destroy_render(render);
	exit(0);
}