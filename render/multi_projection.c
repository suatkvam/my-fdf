#include "render.h"
#include "colors.h"
#include "math3d.h"
#include <math.h>

// Multi-projection wrapper function
t_point2d project_point_multi(t_point point, t_render *render)
{
    switch (render->projection_type)
    {
        case PROJ_ISOMETRIC:
            return (project_isometric(point, render));
        case PROJ_PERSPECTIVE:
            return (project_perspective(point, render));
        case PROJ_ORTHOGRAPHIC:
            return (project_orthographic(point, render));
        case PROJ_TOP_DOWN:
            return (project_top_down(point, render));
        case PROJ_FRONT_VIEW:
            return (project_front_view(point, render));
        case PROJ_SIDE_VIEW:
            return (project_side_view(point, render));
        default:
            return (project_isometric(point, render));
    }
}

// Isometric projection (existing logic)
t_point2d project_isometric(t_point point, t_render *render)
{
    return (project_point_interactive(point, render));
}

// Perspective projection - realistic 3D view
t_point2d project_perspective(t_point point, t_render *render)
{
    t_point2d projected;
    t_3D_vec rotated_point;
    t_matrix4 rotation_matrix;
    float scale, z_depth, perspective_factor;
    
    // Apply rotation using math3d library
    rotation_matrix = matrix4_rotation_y(render->rotation_y);
    rotation_matrix = matrix4_multiply(rotation_matrix, matrix4_rotation_x(render->rotation_x));
    
    t_3D_vec original = {point.x, point.y, point.z};
    rotated_point = matrix4_transform_vec3(rotation_matrix, original);
    
    scale = calculate_scale(render->map) * render->zoom_factor;
    
    // Calculate depth for perspective
    z_depth = rotated_point.z + render->perspective_distance;
    if (z_depth < 1.0)
        z_depth = 1.0; // Avoid division by zero
    
    // Perspective division
    perspective_factor = render->perspective_distance / z_depth;
    
    projected.x = (int)(rotated_point.x * scale * perspective_factor) + WINDOW_WIDTH / 2 + render->offset_x;
    projected.y = (int)(rotated_point.y * scale * perspective_factor) + WINDOW_HEIGHT / 2 + render->offset_y;
    
    projected.color = (point.color == -1) ? COLOR_WHITE : point.color;
    return (projected);
}

// Orthographic projection - no perspective distortion
t_point2d project_orthographic(t_point point, t_render *render)
{
    t_point2d projected;
    t_3D_vec rotated_point;
    t_matrix4 rotation_matrix;
    float scale;
    
    rotation_matrix = matrix4_rotation_y(render->rotation_y);
    rotation_matrix = matrix4_multiply(rotation_matrix, matrix4_rotation_x(render->rotation_x));
    
    t_3D_vec original = {point.x, point.y, point.z};
    rotated_point = matrix4_transform_vec3(rotation_matrix, original);
    
    scale = calculate_scale(render->map) * render->zoom_factor;
    
    // Simple orthographic projection (no perspective)
    projected.x = (int)(rotated_point.x * scale) + WINDOW_WIDTH / 2 + render->offset_x;
    projected.y = (int)(rotated_point.y * scale) + WINDOW_HEIGHT / 2 + render->offset_y;
    
    projected.color = (point.color == -1) ? COLOR_WHITE : point.color;
    return (projected);
}

// Top-down view - perfect for PNG/image heightmaps
t_point2d project_top_down(t_point point, t_render *render)
{
    t_point2d projected;
    float scale;
    
    scale = calculate_scale(render->map) * render->zoom_factor;
    
    // Top-down view: X and Y directly mapped, Z ignored for positioning
    projected.x = (int)(point.x * scale) + WINDOW_WIDTH / 2 + render->offset_x;
    projected.y = (int)(point.y * scale) + WINDOW_HEIGHT / 2 + render->offset_y;
    
    // Use Z for color intensity if no color specified
    if (point.color == -1)
    {
        int intensity = (int)(point.z * 20 + 128); // Convert Z to brightness
        if (intensity < 0) intensity = 0;
        if (intensity > 255) intensity = 255;
        projected.color = (intensity << 16) | (intensity << 8) | intensity; // Grayscale
    }
    else
        projected.color = point.color;
        
    return (projected);
}

// Front view projection
t_point2d project_front_view(t_point point, t_render *render)
{
    t_point2d projected;
    float scale;
    
    scale = calculate_scale(render->map) * render->zoom_factor;
    
    // Front view: X and Z mapping
    projected.x = (int)(point.x * scale) + WINDOW_WIDTH / 2 + render->offset_x;
    projected.y = (int)(-point.z * scale) + WINDOW_HEIGHT / 2 + render->offset_y; // Negative Z for proper orientation
    
    projected.color = (point.color == -1) ? COLOR_WHITE : point.color;
    return (projected);
}

// Side view projection
t_point2d project_side_view(t_point point, t_render *render)
{
    t_point2d projected;
    float scale;
    
    scale = calculate_scale(render->map) * render->zoom_factor;
    
    // Side view: Y and Z mapping
    projected.x = (int)(point.y * scale) + WINDOW_WIDTH / 2 + render->offset_x;
    projected.y = (int)(-point.z * scale) + WINDOW_HEIGHT / 2 + render->offset_y; // Negative Z for proper orientation
    
    projected.color = (point.color == -1) ? COLOR_WHITE : point.color;
    return (projected);
}

// Cycle through projection types
void cycle_projection(t_render *render)
{
    render->projection_type = (render->projection_type + 1) % PROJ_COUNT;
}