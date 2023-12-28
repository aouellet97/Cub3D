#include "cub3d.h"

static void	dda(t_cube *cube, t_raycast *rc)
{
	rc->hit = 0;
	rc->side = 0;
	while (true)
	{
		if (cube->map[rc->map_y][rc->map_x] == '1')
			break ;
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			if (rc->ray_dir_x > 0)
				rc->side = 0;
			else
				rc->side = 1;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			if (rc->ray_dir_y > 0)
				rc->side = 2;
			else
				rc->side = 3;
		}
	}
}

static t_raycast	*calc_dist_ray(t_raycast *rc, int x)
{
	rc->camera_x = 2 * x / (double)SCREENWIDTH - 1;
	rc->ray_dir_x = rc->dir_x + rc->plane_x * rc->camera_x;
	rc->ray_dir_y = rc->dir_y + rc->plane_y * rc->camera_x;
	rc->map_x = (int)rc->pos_x;
	rc->map_y = (int)rc->pos_y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
	return (rc);
}

static void	set_ray_dist_dir(t_raycast *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->pos_y) * rc->delta_dist_y;
	}
}

static void	set_ray_limit(t_raycast *rc)
{
	rc->line_height = (int)(SCREENHEIGHT / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + SCREENHEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + SCREENHEIGHT / 2;
	if (rc->draw_end >= SCREENHEIGHT)
		rc->draw_end = SCREENHEIGHT;
}

void	raycasting_loop(void *arg)
{
	t_cube		*cube;
	t_raycast	*rc;
	int			x;

	cube = (t_cube *)arg;
	rc = cube->raycast;
	x = 0;
	while (x < SCREENWIDTH)
	{
		rc = calc_dist_ray(rc, x);
		set_ray_dist_dir(rc);
		dda(cube, rc);
		if (rc->side < 2)
			rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
		else
			rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
		set_ray_limit(rc);
		cast_floor_ceiling(x, 0, rc);
		display_texture(cube, x);
		key_hook(cube, cube->raycast);
		x++;
	}
}
