#include "cub3d.h"

void	add_path_body(t_cube *cube, char *path, enum e_id id)
{
	if (id == NO)
	{
		if (cube->no_path)
			ft_error(EXISTS);
		cube->no_path = path;
	}
	if (id == SO)
	{
		if (cube->so_path)
			ft_error(EXISTS);
		cube->so_path = path;
	}
	if (id == EA)
	{
		if (cube->ea_path)
			ft_error(EXISTS);
		cube->ea_path = path;
	}
	if (id == WE)
	{
		if (cube->we_path)
			ft_error(EXISTS);
		cube->we_path = path;
	}
}

void	add_path(char *path, enum e_id id)
{
	t_cube	*cube;

	cube = get_cube();
	if (png_verification(path) == ERROR)
		ft_error(NOT_PNG);
	if (open(path, O_RDONLY) == ERROR)
		ft_error(NO_TEXT);
	add_path_body(cube, path, id);
}
