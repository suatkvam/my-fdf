/* format/format.h - clean header for format helpers */
#ifndef FORMAT_H
# define FORMAT_H

# include "math3d.h"
# include <errno.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

/* 3D Mesh structures */
typedef struct s_vertex
{
	t_3D_vec		position;
	t_3D_vec		normal;
	int				color;
}					t_vertex;

typedef struct s_face
{
	int				vertices[3];
}					t_face;

typedef struct s_mesh
{
	t_vertex		*vertices;
	t_face			*faces;
	int				vertex_count;
	int				face_count;
	char			*name;
}					t_mesh;

typedef struct s_stl_loader
{
	size_t			vertices_count;
	t_vertex		*vertices;
	t_face			*faces;
	t_mesh			*mesh;
	uint32_t		triangle_idx;
	int				vertex_idx;
	size_t			current_vertex_idx;
}					t_stl_loader;

/* Image data structure for height maps */
typedef struct s_image_data
{
	unsigned char	*data;
	int				width;
	int				height;
	int				channels;
	char			*filename;
}					t_image_data;

/* File format enum */
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
}					t_file_format;
typedef struct s_ascii_loader
{
	t_vertex		*vertices;
	t_face			*faces;
	size_t			vertex_capacity;
	size_t			face_capacity;
	size_t			vertex_count;
	size_t			face_count;
}					t_ascii_loader;
/* 3D File loaders */
/* The current implementation in read_stl_file.c exposes an fd-based loader */
t_mesh				*load_stl_file_fd(int fd, uint32_t triangle_count);
t_mesh				*load_stl_file(const char *filename);
t_mesh				*load_obj_file(const char *file_name);
t_mesh				*load_ply_file(const char *file_name);
void				free_mesh(t_mesh *mesh);

/* Low-level binary reader helpers (little-endian safe) */
int					read_uint8(int fd, uint8_t *out);
int					read_uint16_le(int fd, uint16_t *out);
int					read_uint32_le(int fd, uint32_t *out);
int					read_float_le(int fd, float *out);
ssize_t				read_binary_chunk(int fd, void *buf, size_t len);

/* Image file loaders */
t_image_data		*load_png_file(const char *file_name);
t_image_data		*load_jpg_file(const char *file_name);
t_image_data		*load_bmp_file(const char *file_name);
void				free_image_data(t_image_data *img);

/* Image to FDF converters */
t_mesh				*image_to_heightmap(t_image_data *img, float height_scale);
int					save_fdf_from_image(const char *image_path,
						const char *fdf_path, float scale);

/* File format detection */
t_file_format		detect_file_format(const char *filename);

#endif /* FORMAT_H */