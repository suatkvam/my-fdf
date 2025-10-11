#include "format.h"
#include "../libft/libft.h"
#include "../get-next-line/get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static int	starts_with(const char *str, const char *prefix)
{
	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

static int	parse_vertex_line(const char *line, t_3D_vec *vertex)
{
	int result;
	
	result = sscanf(line, "%*s %f %f %f", &vertex->x, &vertex->y, &vertex->z);
	printf("parse_vertex_line: sscanf result=%d, line='%s'\n", result, line);
	if (result != 3)
	{
		printf("parse_vertex_line: Failed to parse vertex (expected 3, got %d)\n", result);
		return (-1);
	}
	printf("parse_vertex_line: Parsed vertex: (%f, %f, %f)\n", vertex->x, vertex->y, vertex->z);
	return (0);
}

static int	contains(const char *str, const char *substr)
{
	return (ft_strnstr(str, substr, ft_strlen(str)) != NULL);
}

static int	ensure_vertex_capacity(t_ascii_loader *loader)
{
	size_t		new_cap;
	t_vertex	*new_vertices;

	if (loader->vertex_count >= loader->vertex_capacity)
	{
		new_cap = loader->vertex_capacity ? loader->vertex_capacity * 2 : 64;
		new_vertices = realloc(loader->vertices, sizeof(t_vertex) * new_cap);
		if (!new_vertices)
			return (-1);
		loader->vertices = new_vertices;
		loader->vertex_capacity = new_cap;
	}
	return (0);
}

static int	ensure_face_capacity(t_ascii_loader *loader)
{
	size_t		new_cap;
	t_face		*new_faces;

	if (loader->face_count >= loader->face_capacity)
	{
		new_cap = loader->face_capacity ? loader->face_capacity * 2 : 32;
		new_faces = realloc(loader->faces, sizeof(t_face) * new_cap);
		if (!new_faces)
			return (-1);
		loader->faces = new_faces;
		loader->face_capacity = new_cap;
	}
	return (0);
}

static int	add_triangle_to_loader(t_ascii_loader *loader, t_3D_vec vertices[3])
{
	size_t	start_vertex_idx;
	int		i;

	if (ensure_vertex_capacity(loader) != 0)
		return (-1);
	if (ensure_face_capacity(loader) != 0)
		return (-1);
	start_vertex_idx = loader->vertex_count;
	i = 0;
	while (i < 3)
	{
		loader->vertices[loader->vertex_count].position = vertices[i];
		loader->vertices[loader->vertex_count].normal = (t_3D_vec){0, 0, 0};
		loader->vertices[loader->vertex_count].color = -1;
		loader->vertex_count++;
		i++;
	}
	loader->faces[loader->face_count].vertices[0] = (int)start_vertex_idx;
	loader->faces[loader->face_count].vertices[1] = (int)start_vertex_idx + 1;
	loader->faces[loader->face_count].vertices[2] = (int)start_vertex_idx + 2;
	loader->face_count++;
	return (0);
}

static void	cleanup_loader(t_ascii_loader *loader)
{
	if (!loader)
		return ;
	if (loader->vertices)
		free(loader->vertices);
	if (loader->faces)
		free(loader->faces);
	loader->vertices = NULL;
	loader->faces = NULL;
	loader->vertex_count = 0;
	loader->face_count = 0;
	loader->vertex_capacity = 0;
	loader->face_capacity = 0;
}

static t_mesh	*create_mesh_from_loader(t_ascii_loader *loader)
{
	t_mesh	*mesh;

	if (!loader || loader->vertex_count == 0 || loader->face_count == 0)
		return (NULL);
	mesh = malloc(sizeof(t_mesh));
	if (!mesh)
		return (NULL);
	mesh->vertices = loader->vertices;
	mesh->faces = loader->faces;
	mesh->vertex_count = (int)loader->vertex_count;
	mesh->face_count = (int)loader->face_count;
	mesh->name = NULL;
	loader->vertices = NULL;
	loader->faces = NULL;
	return (mesh);
}

static int	parse_facet(int fd, t_ascii_loader *loader)
{
	char		*line;
	t_3D_vec	vertices[3];
	int			vertex_idx;

	vertex_idx = 0;
	printf("parse_facet: Looking for 'outer loop'\n");
	// "outer loop" satırını oku
	line = get_next_line(fd);
	if (!line)
	{
		printf("parse_facet: get_next_line returned NULL for outer loop\n");
		return (-1);
	}
	printf("parse_facet: Read line: '%s'\n", line);
	if (!contains(line, "outer loop"))
	{
		printf("parse_facet: Line doesn't contain 'outer loop'\n");
		free(line);
		return (-1);
	}
	printf("parse_facet: Found outer loop\n");
	free(line);
	// 3 vertex oku
	while (vertex_idx < 3)
	{
		line = get_next_line(fd);
		if (!line || !contains(line, "vertex"))
		{
			printf("parse_facet: Invalid vertex line: '%s'\n", line ? line : "NULL");
			free(line);
			return (-1);
		}
		printf("parse_facet: Parsing vertex %d: '%s'\n", vertex_idx, line);
		if (parse_vertex_line(line, &vertices[vertex_idx]) != 0)
		{
			free(line);
			return (-1);
		}
		vertex_idx++;
		free(line);
	}
	// "endloop" satırını oku
	line = get_next_line(fd);
	if (!line || !contains(line, "endloop"))
	{
		free(line);
		return (-1);
	}
	free(line);
	// "endfacet" satırını oku
	line = get_next_line(fd);
	if (!line || !contains(line, "endfacet"))
	{
		free(line);
		return (-1);
	}
	free(line);
	// Vertex'leri ve face'i loader'a ekle
	return (add_triangle_to_loader(loader, vertices));
}

t_mesh	*load_stl_ascii_file(const char *filename)
{
	int fd;
	char *line;
	t_ascii_loader loader = {0};
	t_mesh *mesh;

	// 1. Dosyayı aç
	printf("ASCII loader: Opening file %s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("ASCII loader: Failed to open file\n");
		return (NULL);
	}

	// 2. İlk satırı oku: "solid name"
	printf("ASCII loader: Reading first line\n");
	line = get_next_line(fd);
	if (!line)
	{
		printf("ASCII loader: get_next_line returned NULL\n");
		close(fd);
		return (NULL);
	}
	printf("ASCII loader: First line: '%s'\n", line);
	printf("ASCII loader: starts_with result: %d\n", starts_with(line, "solid"));
	printf("ASCII loader: ft_strncmp result: %d\n", ft_strncmp(line, "solid", 5));
	if (!starts_with(line, "solid"))
	{
		printf("ASCII loader: Line doesn't start with 'solid'\n");
		free(line);
		close(fd);
		return (NULL);
	}
	free(line);

	// 3. Ana döngü: facet'leri parse et
	printf("ASCII loader: Starting main loop\n");
	while ((line = get_next_line(fd)))
	{
		printf("ASCII loader: Read line in loop: '%s'\n", line);
		if (contains(line, "facet normal"))
		{
			printf("ASCII loader: Found facet normal, calling parse_facet\n");
			if (parse_facet(fd, &loader) != 0)
			{
				cleanup_loader(&loader);
				free(line);
				close(fd);
				return (NULL);
			}
		}
		else if (starts_with(line, "endsolid"))
		{
			free(line);
			break ;
		}
		free(line);
	}

	// 4. t_mesh oluştur ve döndür
	mesh = create_mesh_from_loader(&loader);
	close(fd);
	return (mesh);
}