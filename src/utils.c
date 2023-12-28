#include "cub3d.h"

int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E');
}

void	find_position(char **map, t_cube *cube, int x, int y)
{
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_map_char(map[y][x]) == true && map[y][x] != '1'
				&& map[y][x] != '0')
			{
				if (map[y][x] == 'N')
					cube->orientation = N;
				if (map[y][x] == 'S')
					cube->orientation = S;
				if (map[y][x] == 'E')
					cube->orientation = E;
				if (map[y][x] == 'W')
					cube->orientation = W;
				cube->start_x = x;
				cube->start_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
