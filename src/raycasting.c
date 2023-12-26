#include "cub3d.h"

int	get_hit(t_cube *cube, t_raycast*rc, mlx_texture_t *texture)
{
	double	hit;
	int buf_x;
	
	hit = 0;
	if (rc->side == 0 || rc->side == 1)
		hit = rc->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		hit = rc->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	hit -= (int) hit;
	buf_x = (int)(hit * (double) texture->width);
	if ((rc->side == 0 || rc->side == 1) && rc->ray_dir_x > 0)
		buf_x = texture->width - buf_x - 1;
	if ((rc->side == 2 || rc->side == 3) && rc->ray_dir_y < 0)
		buf_x = texture->width - buf_x - 1;
	return buf_x;
}

void	draw_texture(mlx_texture_t *texture, uint32_t **buf, int x, int buf_x)
{
	double	dist;
	double	pos;
	int		buf_y; 
	int		j; 
	t_cube *cube;

	cube = get_cube();
	dist = 1.0 * texture->height / cube->raycast->line_height;
	pos = ((double) cube->raycast->draw_start - (double) SCREENHEIGHT / 2
			+ (double) cube->raycast->line_height / 2) * dist;
	if (pos < 0)
		pos = 0;
	j = cube->raycast->draw_start - 1;
	j++;
	while (j < cube->raycast->draw_end)
	{
		buf_y = (int) pos;
		if (pos > texture->height - 1)
			pos = texture->height - 1;
		pos += dist;
		mlx_put_pixel(cube->cubmlx->img_buf , x, j, buf[buf_y][buf_x]);
		j++;	
	}
}


void	display_texture(t_cube *cube, int x)
{
	int buf_x;

	buf_x = 0;
	if (cube->raycast->side == 0)
	{
		buf_x = get_hit(cube, cube->raycast, cube->cubmlx->south_text);
		draw_texture(cube->cubmlx->south_text, cube->cubmlx->s_buffer, x, buf_x);
	}
	else if (cube->raycast->side== 1)
	{
		buf_x = get_hit(cube, cube->raycast, cube->cubmlx->north_text);
		draw_texture(cube->cubmlx->north_text, cube->cubmlx->n_buffer, x, buf_x);
	}
	else if (cube->raycast->side == 2) 
	{
		buf_x = get_hit(cube, cube->raycast, cube->cubmlx->east_text);
		draw_texture(cube->cubmlx->east_text, cube->cubmlx->e_buffer, x, buf_x);
	}
	else if (cube->raycast->side == 3)
	{
		buf_x = get_hit(cube, cube->raycast, cube->cubmlx->west_text);
		draw_texture(cube->cubmlx->west_text, cube->cubmlx->w_buffer, x, buf_x);
	}
}



int is_valid_move(double x, double y)
{
    t_cube *cube = get_cube();

    int map_x = (int)x;
    int map_y = (int)y;

    if (cube->map[map_y][map_x] != '1')
        return (1); 
    return (0); 
}

static void adjust_move(t_raycast *rc, int dir)
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

static void adjust_rotation(t_raycast *rc, int direction)
{
	double	x;

	if (direction == ROTATE_RIGHT)
 	{
		x = rc->dir_x;
		rc->dir_x = x * cos(ROTATE_SPEED ) - rc->dir_y * sin(ROTATE_SPEED);
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

void	key_hook(void)
{
	t_raycast *rc;
	t_cube*cube;
	
	cube = get_cube();
	rc = cube->raycast;
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

static void set_vars_raycast(t_cube *cube, t_raycast *rc)
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

void set_raycast_vars(t_raycast *rc)
{

	t_cube *cube;
	
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



static void cast_floor_ceiling(int x, int y, t_raycast *rc)
{
	unsigned int pixel_color;
	t_cube *cube;
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

static void dda(t_cube *cube, t_raycast *rc)
{
	rc->hit = 0; 
	rc->side = 0;
	while (true)
	{
		if(cube->map[rc->map_y][rc->map_x] == '1') 
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

static t_raycast *calc_dist_ray(t_raycast *rc, int x)
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

static void set_ray_dist_dir(t_raycast *rc)
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

static void set_ray_limit(t_raycast *rc)
{
	rc->line_height = (int)(SCREENHEIGHT / rc->perp_wall_dist);
    rc->draw_start = -rc->line_height / 2 + SCREENHEIGHT / 2;
    if (rc->draw_start < 0) 
        rc->draw_start = 0;
    rc->draw_end = rc->line_height / 2 + SCREENHEIGHT / 2;
    if (rc->draw_end >= SCREENHEIGHT) 
        rc->draw_end = SCREENHEIGHT;
} 

void raycasting_loop(void *arg)
{
	t_cube	*cube;
	t_raycast *rc;
	int x;
	int y;

	cube = (t_cube*)arg;
	rc = cube->raycast;
	y = 0;
	x = 0;
	while(x < SCREENWIDTH)
	{
		rc = calc_dist_ray(rc, x);
		set_ray_dist_dir(rc);
		dda(cube, rc);
		if (rc->side< 2)
			rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
		else
			rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
		set_ray_limit(rc);
		cast_floor_ceiling(x, 0, rc);
		display_texture(cube,x);
		key_hook();
		x++;
	}
	usleep(1000);
}	
