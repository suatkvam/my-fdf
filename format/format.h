#ifndef FORMAT_H
# define FORMAT_H

# include "math3d.h"

// Image data structure for height maps
typedef struct s_image_data
{
    unsigned char			*data;
    int						width;
    int						height;
    int						channels;
    char					*filename;
}							t_image_data;

// 3D Mesh structures  
typedef struct s_vertex
{
    t_3D_vec					position;
    t_3D_vec					normal;
    int						color;
}							t_vertex;

typedef struct s_face
{
    int						vertices[3]; // Triangle indices
}							t_face;

typedef struct s_mesh
{
    t_vertex				*vertices;
    t_face					*faces;
    int						vertex_count;
    int						face_count;
    char					*name;
}							t_mesh;

// File format detection
typedef enum e_file_format
{
    FORMAT_UNKNOWN = 0,
    FORMAT_FDF,
    FORMAT_STL,
    FORMAT_OBJ,
    FORMAT_PLY,
    FORMAT_PNG,
    FORMAT_JPG,
    FORMAT_BMP
}							t_file_format;

// 3D File loaders
t_mesh						*load_stl_file(const char *file_name);
t_mesh						*load_obj_file(const char *file_name);
t_mesh						*load_ply_file(const char *file_name);
void						free_mesh(t_mesh *mesh);

// Image file loaders (for height map conversion)
t_image_data				*load_png_file(const char *file_name);
t_image_data				*load_jpg_file(const char *file_name);
t_image_data				*load_bmp_file(const char *file_name);
void						free_image_data(t_image_data *img);

// Image to FDF converters
t_mesh						*image_to_heightmap(t_image_data *img, float height_scale);
int							save_fdf_from_image(const char *image_path, const char *fdf_path, float scale);

// File format detection
t_file_format				detect_file_format(const char *filename);

#endif