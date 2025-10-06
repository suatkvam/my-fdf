#include "render.h"
#include "colors.h"
#include "stdlib.h"

// Clear image to black
void clear_image(t_render *render)
{
    int x;
    int y;
    y= 0;
    while(y < render->window_height)
    {
        x = 0;
        while (x < render->window_width)
        {
            put_pixel(render,x,y,COLOR_BLACK);
            x++;
        }
        y++;
    }
}

//TODO BUNLAR PARÇALANIP AYARLANACAK
// Simple isometric projection
t_point2d project_point(t_point point)
{
    t_point2d projected;
    float scale;
    
    scale = 20.0; // Zoom factor
    
    // Isometric projection formula
    projected.x = (point.x - point.y) * scale + 500; // Center X
    projected.y = (point.x + point.y - point.z) * scale * 0.5 + 300; // Center Y
    
    // Use point color or default white
    if (point.color == -1)
        projected.color = COLOR_WHITE;
    else
        projected.color = point.color;
        
    return (projected);
}

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
            current_2d = project_point(current_point);
            
            // Draw line to right neighbor (if exists)
            if (x < render->map->width - 1)
            {
                right_2d = project_point(render->map->grid[y][x + 1]);
                draw_line_hybrid(render, current_2d, right_2d);
            }
            
            // Draw line to bottom neighbor (if exists)
            if (y < render->map->height - 1)
            {
                down_2d = project_point(render->map->grid[y + 1][x]);
                draw_line_hybrid(render, current_2d, down_2d);
            }
            
            x++;
        }
        y++;
    }
    
    // Update display
    mlx_put_image_to_window(render->mlx, render->window, render->image, 0, 0);
}

// Main render initialization and loop
int start_render(t_render *render)
{
    if (!render)
        return (1);
        
    // Initial render
    render_map(render);
    
    // Set up event handlers
    mlx_key_hook(render->window, key_press_handler, render);
    mlx_hook(render->window, 17, 0, close_window_handler, render); // X button
    
    // Start MLX loop
    mlx_loop(render->mlx);
    
    return (0);
}