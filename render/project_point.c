#include "render.h"
#include "colors.h"

// Calculate scale based on map dimensions
float calculate_scale(t_map *map)
{
    int max_dimension;
    
    if (!map)
        return (20.0);
        
    max_dimension = (map->width > map->height) ? map->width : map->height;
    
    // Scale based on map size
    if (max_dimension <= 10)
        return (40.0);      // Very small maps
    else if (max_dimension <= 20)
        return (30.0);      // Small maps (like test files)
    else if (max_dimension <= 50)
        return (20.0);      // Medium maps
    else if (max_dimension <= 100)
        return (6.0);       // Large maps (like t2: 100x100)
    else if (max_dimension <= 300)
        return (4.0);       // Very large maps
    else
        return (1.3);       // Huge maps (like julia.fdf 500x500)
}

// Simple isometric projection with adaptive scaling
t_point2d project_point_scaled(t_point point, t_map *map)
{
    t_point2d projected;
    float scale, z_factor;
    
    scale = calculate_scale(map);
    
    // Z scaling based on map shape and size
    if (map->width <= 50 || map->height <= 50)
    {
        z_factor = 0.6;    // Small maps - more dramatic
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
    projected.y = (point.x + point.y - point.z * z_factor) * scale * 0.5 + WINDOW_HEIGHT / 4; // Adaptive Z factor
    
    // Use point color or default white
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