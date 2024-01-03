/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:07:22 by wmillett          #+#    #+#             */
/*   Updated: 2024/01/03 15:07:23 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *message)
{
	gc_free_all();
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	write(2, "\n", 1);
	ft_putstr_fd(WHITE, 2);
	exit(1);
}

void	clear_mlx(t_cubmlx *cmlx)
{
	if (cmlx->north_text)
		mlx_delete_texture(cmlx->north_text);
	if (cmlx->south_text)
		mlx_delete_texture(cmlx->south_text);
	if (cmlx->east_text)
		mlx_delete_texture(cmlx->east_text);
	if (cmlx->west_text)
		mlx_delete_texture(cmlx->west_text);
	if (cmlx->img_buf)
		mlx_delete_image(cmlx->mlx, cmlx->img_buf);
	if (cmlx->mlx)
		mlx_terminate(cmlx->mlx);
}
