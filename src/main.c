/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:07:41 by wmillett          #+#    #+#             */
/*   Updated: 2024/01/03 15:07:42 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cube	*get_cube(void)
{
	static t_cubmlx		cubmlx;
	static t_cube		cube;
	static t_raycast	raycast;

	cube.cubmlx = &cubmlx;
	cube.raycast = &raycast;
	return (&cube);
}

void	print_tab(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = get_cube();
	cube->cubmlx->north_text = NULL;
	cube->cubmlx->south_text = NULL;
	cube->cubmlx->east_text = NULL;
	cube->cubmlx->west_text = NULL;
	cube->cubmlx->img_buf = NULL;
	cube->cubmlx->mlx = NULL;
	if (argc < 2)
		ft_error(NO_MAP);
	if (file_verification(argv[1], "cub") == ERROR)
		ft_error(NOT_CUB);
	cube->fd = open(argv[1], O_RDONLY);
	if (cube->fd == ERROR)
		ft_error(FD_ERROR);
	read_file(cube);
	if (!cube->content)
		ft_error(READ_ERROR);
	parsing(get_cube());
	mlx_start(cube);
	gc_free_all();
	return (SUCESS);
}
