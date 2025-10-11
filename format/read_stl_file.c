#include "format.h"
#include <stdlib.h>

static int	setup_stl_loader(t_stl_loader *loader, uint32_t triangle_count)
{
	if (!loader)
		return (-1);
	loader->vertices_count = (size_t)triangle_count * 3;
	loader->triangle_idx = 0;
	loader->vertex_idx = 0;
	loader->current_vertex_idx = 0;
	loader->mesh = NULL;
	loader->vertices = malloc(sizeof(*loader->vertices)
			* loader->vertices_count);
	loader->faces = malloc(sizeof(*loader->faces) * triangle_count);
	if (!loader->vertices || !loader->faces)
	{
		if (loader->vertices)
			free(loader->vertices);
		if (loader->faces)
			free(loader->faces);
		return (-1);
	}
	return (0);
}

static int	read_triangle_data(int fd, t_3D_vec *normal, t_3D_vec vertices[3])
{
	int	i;

	if (read_float_le(fd, &normal->x) != 0)
		return (-1);
	if (read_float_le(fd, &normal->y) != 0)
		return (-1);
	if (read_float_le(fd, &normal->z) != 0)
		return (-1);
	i = 0;
	while (i < 3)
	{
		if (read_float_le(fd, &vertices[i].x) != 0)
			return (-1);
		if (read_float_le(fd, &vertices[i].y) != 0)
			return (-1);
		if (read_float_le(fd, &vertices[i].z) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	process_triangle(int fd, t_stl_loader *loader)
{
	t_3D_vec	normal;
	t_3D_vec	vertices[3];
	uint16_t	attr;

	if (read_triangle_data(fd, &normal, vertices) != 0)
		return (-1);
	loader->vertex_idx = 0;
	while (loader->vertex_idx < 3)
	{
		loader->current_vertex_idx = loader->triangle_idx * 3
			+ loader->vertex_idx;
		loader->vertices[loader->current_vertex_idx].position = vertices[loader->vertex_idx];
		loader->vertices[loader->current_vertex_idx].normal = normal;
		loader->vertices[loader->current_vertex_idx].color = -1;
		loader->faces[loader->triangle_idx].vertices[loader->vertex_idx] = (int)loader->current_vertex_idx;
		loader->vertex_idx++;
	}
	if (read_uint16_le(fd, &attr) != 0)
		return (-1);
	return (0);
}

static void	cleanup_loader(t_stl_loader *loader)
{
	if (!loader)
		return ;
	if (loader->vertices)
		free(loader->vertices);
	if (loader->faces)
		free(loader->faces);
	if (loader->mesh)
		free(loader->mesh);
}

t_mesh	*load_stl_file_fd(int fd, uint32_t triangle_count)
{
	t_stl_loader	loader;

	if (setup_stl_loader(&loader, triangle_count) != 0)
		return (NULL);
	loader.triangle_idx = 0;
	while (loader.triangle_idx < triangle_count)
	{
		if (process_triangle(fd, &loader) != 0)
		{
			cleanup_loader(&loader);
			return (NULL);
		}
		loader.triangle_idx++;
	}
	loader.mesh = malloc(sizeof(*loader.mesh));
	if (!loader.mesh)
	{
		cleanup_loader(&loader);
		return (NULL);
	}
	loader.mesh->vertices = loader.vertices;
	loader.mesh->faces = loader.faces;
	loader.mesh->vertex_count = (int)loader.vertices_count;
	loader.mesh->face_count = (int)triangle_count;
	loader.mesh->name = NULL;
	return (loader.mesh);
}
