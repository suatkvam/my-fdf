#include "render.h"
#include <stdio.h>

// Wrapper for expose hook
int expose_handler(t_render *render)
{
    render_map(render);
    return (0);
}

// Main render initialization and loop
int start_render(t_render *render)
{
    if (!render)
        return (1);
        
    // Initial render
    printf("Rendering initial map...\n");
    render_map(render);
    printf("Map rendered, setting up event handlers...\n");
    
    // Set up event handlers
    mlx_key_hook(render->window, handle_key_press, render);
    mlx_hook(render->window, 17, 0, close_window, render); // X button
    mlx_mouse_hook(render->window, handle_mouse_wheel, render); // Mouse wheel
    mlx_expose_hook(render->window, expose_handler, render); // Redraw on expose
    
    // Start MLX loop
    printf("Starting MLX loop...\n");
    mlx_loop(render->mlx);
    
    return (0);
}
