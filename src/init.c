/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:07:36 by wmillett          #+#    #+#             */
/*   Updated: 2024/01/03 15:09:39 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_infos(t_cube *cube)
{
	cube->no_path = NULL;
	cube->so_path = NULL;
	cube->ea_path = NULL;
	cube->we_path = NULL;
	cube->c_red = -1;
	cube->c_green = -1;
	cube->c_blue = -1;
	cube->f_red = -1;
	cube->f_green = -1;
	cube->f_blue = -1;
}

void	get_map_infos(t_cube *cube, char *content)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (content[i])
	{
		len = 0;
		while (content[i] && content[i] != '\n')
		{
			if (content[i] == '\t')
				len += 3 - ((len) % 4);
			len++;
			i++;
		}
		if (content[i] == '\n')
			cube->y_size++;
		if (len > cube->x_size)
			cube->x_size = len;
		if (content[i])
			i++;
	}
}

static void	populate_map(char **map, char *content)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (content[i])
	{
		j = 0;
		while (content[i] && content[i] != '\n')
		{
			if (content[i] == '\t')
				j += (4 - ((j) % 4) - 1);
			if (is_whitespace(content[i]) == false)
				map[k][j] = content[i];
			j++;
			i++;
		}
		if (content[i] == '\n')
			k++;
		if (content[i])
			i++;
	}
}

char	**get_map(t_cube *cube, char *content)
{
	char	**map;
	int		i;

	i = 0;
	map = NULL;
	cube->y_size = 0;
	cube->x_size = 0;
	get_map_infos(cube, content);
	map = gc_malloc(sizeof(char *) * (cube->y_size + 2));
	map[cube->y_size + 1] = NULL;
	i = 0;
	while (i < cube->y_size + 1)
	{
		map[i] = gc_malloc(sizeof(char) * (cube->x_size + 1));
		map[i][cube->x_size] = 0;
		ft_memset(map[i], '-', cube->x_size);
		i++;
	}
	populate_map(map, content);
	cube->height = cube->y_size + 1;
	cube->width = cube->x_size;
	return (map);
}
