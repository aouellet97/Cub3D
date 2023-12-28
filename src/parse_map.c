#include "cub3d.h"

int	find_map_start(char *content)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			i++;
			start = i;
			while (content[i] && is_whitespace(content[i]) == true
				&& content[i] != 10)
				i++;
			if (content[i] == '0' || content[i] == '1')
				return (start);
		}
		else
			i++;
	}
	return (-1);
}

void	validate_map(char *content)
{
	static int	count = 0;
	int			i;

	i = 0;
	while (content[i])
	{
		if (content[i] == 'N' || content[i] == 'S' || content[i] == 'W'
			|| content[i] == 'E')
			count++;
		if (count > 1)
			ft_error(MANY_POS);
		if (is_whitespace(content[i]) == false && (content[i] != '1'
				&& content[i] != '0' && content[i] != 'N' && content[i] != 'S'
				&& content[i] != 'W' && content[i] != 'E'))
			ft_error(WEIRD_CHAR);
		i++;
	}
	if (count == 0)
		ft_error(NO_POS);
}

void	flood_fill(t_cube *cube, int y, int x)
{
	if (cube->map[y][x] == '-' || x == 0 || y == 0 || x == get_cube()->x_size
		- 1 || y == get_cube()->y_size) //change to space
		ft_error(MAP_OPEN);
	if (cube->map[y][x] == '0')
		cube->map[y][x] = 'X';
	if (cube->map[y][x + 1] && cube->map[y][x + 1] != '1' && cube->map[y][x
		+ 1] != 'X')
		flood_fill(cube, y, x + 1);
	if (cube->map[y][x - 1] && cube->map[y][x - 1] != '1' && cube->map[y][x
		- 1] != 'X')
		flood_fill(cube, y, x - 1);
	if (cube->map[y + 1] && cube->map[y + 1][x] != '1' && cube->map[y
		+ 1][x] != 'X')
		flood_fill(cube, y + 1, x);
	if (cube->map[y - 1] && cube->map[y - 1][x] != '1' && cube->map[y
		- 1][x] != 'X')
		flood_fill(cube, y - 1, x);
}
