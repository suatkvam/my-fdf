#include "render.h"
#include "colors.h"
#include <math.h>

// Calculate scale based on map dimensions
float calculate_scale(t_map *map)
{
    int max_dimension;
    
    if (!map)
        return (20.0);
        
    if (map->width > map->height)
        max_dimension = map->width;
    else
        max_dimension = map->height;
    
    // Scale based on map size groups
    if (max_dimension <= 5)
        return (100.0);     // GROUP 1: Micro maps (test_color: 3x2, test_small: 5x5)
    else if (max_dimension <= 10)
        return (50.0);      // GROUP 2: Tiny maps (10-2, cube, elem: 10x10)
    else if (max_dimension <= 15)
        return (35.0);      // GROUP 3: Very small maps (basictest: 11x9, plat: 10x13)
    else if (max_dimension <= 25)
        return (25.0);      // GROUP 4: Small maps (42: 19x11, 20-60: 20x20, grid: 21x8)
    else if (max_dimension <= 35)
        return (15.0);      // GROUP 5: Small-medium maps (pyra: 27x27, pyramide: 27x33)
    else if (max_dimension <= 50)
        return (12.0);      // GROUP 6: Medium maps (pylone: 48x47, 50-4: 50x50)
    else if (max_dimension <= 100)
        return (6.0);       // GROUP 7: Large maps (100-6: 100x100, t2: 100x100)
    else if (max_dimension <= 200)
        return (3.0);       // GROUP 8: Very large maps (mars: 200x116, t1: 200x200)
    else
        return (1.0);       // GROUP 9: Huge maps (julia: 500x500, elem-fract: 500x500)
}

// Simple isometric projection with adaptive scaling
t_point2d project_point_scaled(t_point point, t_map *map)
{
    t_point2d projected;
    float scale, z_factor;
    
    scale = calculate_scale(map);
    
    // Z scaling based on map shape and size
    if (map->width <= 15 || map->height <= 15)
    {
        z_factor = 1.2;    // Very small maps - very dramatic (10-2, basictest)
    }
    else if (map->width <= 50 || map->height <= 50)
    {
        // Special handling for pyramid maps
        if (map->width >= 25 && map->height >= 25)
            z_factor = 1.8;    // Pyramid maps - extra dramatic
        else
            z_factor = 0.8;    // Other small maps
    }
    else if (map->width <= 200 || map->height <= 200)
    {
        // Check if map is square or rectangular
        float aspect_ratio = (float)map->width / (float)map->height;
        if (aspect_ratio >= 0.8 && aspect_ratio <= 1.2)
            z_factor = 0.4;    // Square maps (like t1: 200x200)
        else
            z_factor = 2.0;    // Rectangular maps (like mars: 200x116) - more dramatic
    }
    else
    {
        z_factor = 0.2;    // Large maps - less dramatic
    }
    
    // Isometric projection formula with adaptive Z scaling
    projected.x = (point.x - point.y) * scale + WINDOW_WIDTH / 2; // Center X
    
    // Special Y positioning for elem2 (20x20 square maps)
    if (map->width == 20 && map->height == 20)
        projected.y = (point.x + point.y - point.z * z_factor) * scale * 0.5 + WINDOW_HEIGHT / 2; // lower down
    else
        projected.y = (point.x + point.y - point.z * z_factor) * scale * 0.5 + WINDOW_HEIGHT / 4; // Normal
    
    // Use point color or default white
    if (point.color == -1)
        projected.color = COLOR_WHITE;
    else
        projected.color = point.color;
        
    return (projected);
}

// Interactive projection with offset and rotation support
t_point2d project_point_interactive(t_point point, t_render *render)
{
    t_point2d projected;
    float scale, z_factor;
    float rotated_x, rotated_y;
    
    scale = calculate_scale(render->map) * render->zoom_factor;
    
    // Apply rotation (simple Y-axis rotation for now)
    rotated_x = point.x * cos(render->rotation_y) - point.y * sin(render->rotation_y);
    rotated_y = point.x * sin(render->rotation_y) + point.y * cos(render->rotation_y);
    
    // Z scaling (same as before)
    if (render->map->width <= 15 || render->map->height <= 15)
        z_factor = 1.2;
    else if (render->map->width <= 50 || render->map->height <= 50)
    {
        if (render->map->width >= 25 && render->map->height >= 25)
            z_factor = 1.8;
        else
            z_factor = 0.8;
    }
    else if (render->map->width <= 200 || render->map->height <= 200)
    {
        float aspect_ratio = (float)render->map->width / (float)render->map->height;
        if (aspect_ratio >= 0.8 && aspect_ratio <= 1.2)
            z_factor = 0.4;
        else
            z_factor = 2.0;
    }
    else
        z_factor = 0.2;
    
    // Isometric projection with offsets
    projected.x = (rotated_x - rotated_y) * scale + WINDOW_WIDTH / 2 + render->offset_x;
    
    if (render->map->width == 20 && render->map->height == 20)
        projected.y = (rotated_x + rotated_y - point.z * z_factor) * scale * 0.5 + WINDOW_HEIGHT / 6 + render->offset_y;
    else
        projected.y = (rotated_x + rotated_y - point.z * z_factor) * scale * 0.5 + WINDOW_HEIGHT / 4 + render->offset_y;
    
    if (point.color == -1)
        projected.color = COLOR_WHITE;
    else
        projected.color = point.color;
        
    return (projected);
}

// Backward compatibility wrapper
t_point2d project_point(t_point point)
{
    t_point2d projected;
    float scale = 20.0; // Default scale
    
    // Isometric projection formula with Z scaling
    projected.x = (point.x - point.y) * scale + WINDOW_WIDTH / 2; // Center X
    projected.y = (point.x + point.y - point.z * 0.3) * scale * 0.5 + WINDOW_HEIGHT / 3; // Z factor reduced
    
    // Use point color or default white
    if (point.color == -1)
        projected.color = COLOR_WHITE;
    else
        projected.color = point.color;
        
    return (projected);
}