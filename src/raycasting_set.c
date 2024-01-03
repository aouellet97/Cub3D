/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:07:57 by wmillett          #+#    #+#             */
/*   Updated: 2024/01/03 15:07:58 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_vars_raycast(t_cube *cube, t_raycast *rc)
{
	if (cube->orientation == E)
	{
		rc->dir_x = 1;
		rc->dir_y = 0;
		rc->plane_x = 0;
		rc->plane_y = 0.66;
	}
	else if (cube->orientation == W)
	{
		rc->dir_x = -1;
		rc->dir_y = 0;
		rc->plane_x = 0;
		rc->plane_y = -0.66;
	}
}

void	set_raycast_vars(t_raycast *rc)
{
	t_cube	*cube;

	cube = get_cube();
	rc->pos_x = (double)cube->start_x + 0.5;
	rc->pos_y = (double)cube->start_y + 0.5;
	if (cube->orientation == N)
	{
		rc->dir_x = 0;
		rc->dir_y = -1;
		rc->plane_x = 0.66;
		rc->plane_y = 0;
	}
	else if (cube->orientation == S)
	{
		rc->dir_x = 0;
		rc->dir_y = 1;
		rc->plane_x = -0.66;
		rc->plane_y = 0;
	}
	else
		set_vars_raycast(cube, rc);
}
