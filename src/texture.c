#include "cub3d.h"

void	cast_floor_ceiling(int x, int y, t_raycast *rc)
{
	unsigned int	pixel_color;
	t_cube			*cube;

	(void)rc;
	cube = get_cube();
	while (y < SCREENHEIGHT)
	{
		if (y < SCREENHEIGHT / 2)
			pixel_color = cube->cubmlx->ceiling_color; // Color for the ceiling
		else
			pixel_color = cube->cubmlx->floor_color; // Color for the floor
		mlx_put_pixel(cube->cubmlx->img_buf, x, y, pixel_color);
		y++;
	}
}

static int	get_hit(t_raycast *rc, mlx_texture_t *texture)
{
	double	hit;
	int		buf_x;

	hit = 0;
	if (rc->side == 0 || rc->side == 1)
		hit = rc->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		hit = rc->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	hit -= (int)hit;
	buf_x = (int)(hit * (double)texture->width);
	if ((rc->side == 0 || rc->side == 1) && rc->ray_dir_x > 0)
		buf_x = texture->width - buf_x - 1;
	if ((rc->side == 2 || rc->side == 3) && rc->ray_dir_y < 0)
		buf_x = texture->width - buf_x - 1;
	return (buf_x);
}

static void	draw_texture(mlx_texture_t *texture, uint32_t **buf, int x,
		int buf_x)
{
	double	dist;
	double	pos;
	int		buf_y;
	int		j;
	t_cube	*cube;

	cube = get_cube();
	dist = 1.0 * texture->height / cube->raycast->line_height;
	pos = ((double)cube->raycast->draw_start - (double)SCREENHEIGHT / 2
			+ (double)cube->raycast->line_height / 2) * dist;
	if (pos < 0)
		pos = 0;
	j = cube->raycast->draw_start - 1;
	j++;
	while (j < cube->raycast->draw_end)
	{
		buf_y = (int)pos;
		if (pos > texture->height - 1)
			pos = texture->height - 1;
		pos += dist;
		mlx_put_pixel(cube->cubmlx->img_buf, x, j, buf[buf_y][buf_x]);
		j++;
	}
}

void	display_texture(t_cube *cube, int x)
{
	int	buf_x;

	buf_x = 0;
	if (cube->raycast->side == 0)
	{
		buf_x = get_hit(cube->raycast, cube->cubmlx->south_text);
		draw_texture(cube->cubmlx->south_text, cube->cubmlx->s_buffer, x,
			buf_x);
	}
	else if (cube->raycast->side == 1)
	{
		buf_x = get_hit(cube->raycast, cube->cubmlx->north_text);
		draw_texture(cube->cubmlx->north_text, cube->cubmlx->n_buffer, x,
			buf_x);
	}
	else if (cube->raycast->side == 2)
	{
		buf_x = get_hit(cube->raycast, cube->cubmlx->east_text);
		draw_texture(cube->cubmlx->east_text, cube->cubmlx->e_buffer, x, buf_x);
	}
	else if (cube->raycast->side == 3)
	{
		buf_x = get_hit(cube->raycast, cube->cubmlx->west_text);
		draw_texture(cube->cubmlx->west_text, cube->cubmlx->w_buffer, x, buf_x);
	}
}
