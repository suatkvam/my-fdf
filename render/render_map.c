#include "render.h"

// Render the entire map
void render_map(t_render *render)
{
    int x, y;
    t_point current_point;
    t_point2d current_2d, right_2d, down_2d;
    
    if (!render || !render->map)
        return;
        
    // Clear screen
    clear_image(render);
    
    // Draw grid - connect each point to its neighbors
    y = 0;
    while (y < render->map->height)
    {
        x = 0;
        while (x < render->map->width)
        {
            current_point = render->map->grid[y][x];
            current_2d = project_point_multi(current_point, render);
            
            // Draw line to right neighbor (if exists)
            if (x < render->map->width - 1)
            {
                right_2d = project_point_multi(render->map->grid[y][x + 1], render);
                draw_line_hybrid(render, current_2d, right_2d);
            }
            
            // Draw line to bottom neighbor (if exists)
            if (y < render->map->height - 1)
            {
                down_2d = project_point_multi(render->map->grid[y + 1][x], render);
                draw_line_hybrid(render, current_2d, down_2d);
            }
            
            x++;
        }
        y++;
    }
    
    // Update display
    mlx_put_image_to_window(render->mlx, render->window, render->image, 0, 0);
}