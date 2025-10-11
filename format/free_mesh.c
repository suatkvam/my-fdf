#include "format.h"
#include <stdlib.h>

void	free_mesh(t_mesh *mesh)
{
	if (!mesh)
		return ;
	if (mesh->vertices)
		free(mesh->vertices);
	if (mesh->faces)
		free(mesh->faces);
	if (mesh->name)
		free(mesh->name);
	free(mesh);
}