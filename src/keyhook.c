/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:07:38 by wmillett          #+#    #+#             */
/*   Updated: 2024/01/03 15:07:39 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_move(double x, double y)
{
	t_cube	*cube;
	int		map_x;
	int		map_y;

	cube = get_cube();
	map_x = (int)x;
	map_y = (int)y;
	if (cube->map[map_y][map_x] != '1')
		return (1);
	return (0);
}

static void	adjust_move(t_raycast *rc, int dir)
{
	if (dir == MOVE_UP)
	{
		rc->new_x += rc->dir_x * MOVE_SPEED;
		rc->new_y += rc->dir_y * MOVE_SPEED;
	}
	if (dir == MOVE_DOWN)
	{
		rc->new_x -= rc->dir_x * MOVE_SPEED;
		rc->new_y -= rc->dir_y * MOVE_SPEED;
	}
	if (dir == MOVE_LEFT)
	{
		rc->new_x -= rc->plane_x * MOVE_SPEED;
		rc->new_y -= rc->plane_y * MOVE_SPEED;
	}
	if (dir == MOVE_RIGHT)
	{
		rc->new_x += rc->plane_x * MOVE_SPEED;
		rc->new_y += rc->plane_y * MOVE_SPEED;
	}
}

static void	adjust_rotation(t_raycast *rc, int direction)
{
	double	x;

	if (direction == ROTATE_RIGHT)
	{
		x = rc->dir_x;
		rc->dir_x = x * cos(ROTATE_SPEED) - rc->dir_y * sin(ROTATE_SPEED);
		rc->dir_y = x * sin(ROTATE_SPEED) + rc->dir_y * cos(ROTATE_SPEED);
		x = rc->plane_x;
		rc->plane_x = x * cos(ROTATE_SPEED) - rc->plane_y * sin(ROTATE_SPEED);
		rc->plane_y = x * sin(ROTATE_SPEED) + rc->plane_y * cos(ROTATE_SPEED);
	}
	if (direction == ROTATE_LEFT)
	{
		x = rc->dir_x;
		rc->dir_x = x * cos(-ROTATE_SPEED) - rc->dir_y * sin(-ROTATE_SPEED);
		rc->dir_y = x * sin(-ROTATE_SPEED) + rc->dir_y * cos(-ROTATE_SPEED);
		x = rc->plane_x;
		rc->plane_x = x * cos(-ROTATE_SPEED) - rc->plane_y * sin(-ROTATE_SPEED);
		rc->plane_y = x * sin(-ROTATE_SPEED) + rc->plane_y * cos(-ROTATE_SPEED);
	}
}

void	key_hook(t_cube *cube, t_raycast *rc)
{
	rc->new_x = rc->pos_x;
	rc->new_y = rc->pos_y;
	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->cubmlx->mlx);
	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_W))
		adjust_move(rc, MOVE_UP);
	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_S))
		adjust_move(rc, MOVE_DOWN);
	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_A))
		adjust_move(rc, MOVE_LEFT);
	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_D))
		adjust_move(rc, MOVE_RIGHT);
	if (is_valid_move(rc->new_x, rc->pos_y))
		rc->pos_x = rc->new_x;
	if (is_valid_move(rc->pos_x, rc->new_y))
		rc->pos_y = rc->new_y;
	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_RIGHT))
		adjust_rotation(rc, ROTATE_RIGHT);
	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_LEFT))
		adjust_rotation(rc, ROTATE_LEFT);
}
