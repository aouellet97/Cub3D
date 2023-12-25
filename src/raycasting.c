#include "cub3d.h"

#define COLOR_NORTH 0x0000FFFF  
#define COLOR_SOUTH 0x00FF00FF  
#define COLOR_EAST  0xFF00FFFF  
#define COLOR_WEST  0x00FFFFFF  

int is_valid_move(double x, double y)
{
    t_cube *cube = get_cube();

    int map_x = (int)x;
    int map_y = (int)y;

    if (cube->map[map_y][map_x] != '1')
    {
        return 1; 
    }

    return 0; 
}

 void	key_hook(void)
 {
 	
	t_cube*cube = get_cube();
	t_raycast *rc = cube->raycast;

    double new_x = rc->pos_x;
    double new_y = rc->pos_y;

 	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_ESCAPE))
 	 	mlx_close_window(cube->cubmlx->mlx);

    if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_W))
    {
        new_x += rc->dir_x * MOVE_SPEED;
        new_y += rc->dir_y * MOVE_SPEED;
    }
    if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_S))
    {
        new_x -= rc->dir_x * MOVE_SPEED;
        new_y -= rc->dir_y * MOVE_SPEED;
    }

    if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_A))
    {
        new_x -= rc->plane_x * MOVE_SPEED;
        new_y -= rc->plane_y * MOVE_SPEED;
    }
    if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_D))
    {
        new_x += rc->plane_x * MOVE_SPEED;
        new_y += rc->plane_y * MOVE_SPEED;
    }


    if (is_valid_move(new_x, rc->pos_y))
    {
        rc->pos_x = new_x;
    }

    if (is_valid_move(rc->pos_x, new_y))
    {
        rc->pos_y = new_y;
    }

 	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_RIGHT))
 		{
			double	x;

			x = rc->dir_x;
			rc->dir_x = x * cos(ROTATE_SPEED ) - rc->dir_y * sin(ROTATE_SPEED);
			rc->dir_y = x * sin(ROTATE_SPEED) + rc->dir_y * cos(ROTATE_SPEED);

			x = rc->plane_x;
			rc->plane_x = x * cos(ROTATE_SPEED) - rc->plane_y * sin(ROTATE_SPEED);
			rc->plane_y = x * sin(ROTATE_SPEED) + rc->plane_y * cos(ROTATE_SPEED);
 		}
 	if (mlx_is_key_down(cube->cubmlx->mlx, MLX_KEY_LEFT))
 		{
			double	x;

			x = rc->dir_x;
			rc->dir_x = x * cos(-ROTATE_SPEED) - rc->dir_y * sin(-ROTATE_SPEED);
			rc->dir_y = x * sin(-ROTATE_SPEED) + rc->dir_y * cos(-ROTATE_SPEED);

			x = rc->plane_x;
			rc->plane_x = x * cos(-ROTATE_SPEED) - rc->plane_y * sin(-ROTATE_SPEED);
			rc->plane_y = x * sin(-ROTATE_SPEED) + rc->plane_y * cos(-ROTATE_SPEED);
 		}
 }
	



void set_raycast_vars(t_raycast*rc)
{

	t_cube *cube = get_cube();
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
else if (cube->orientation == E)
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
		rc->camera_x = 2 * x / (double)SCREENWIDTH - 1;
        rc->ray_dir_x = rc->dir_x + rc->plane_x * rc->camera_x;
        rc->ray_dir_y = rc->dir_y + rc->plane_y * rc->camera_x;
	
	 	rc->map_x = (int)rc->pos_x;
        rc->map_y = (int)rc->pos_y;

	    rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
        rc->delta_dist_y = fabs(1 / rc->ray_dir_y);

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
		
	// DDA
 	rc->hit = 0; 
	rc->side = 0;

	while (1)
	{
		if(cube->map[rc->map_y][rc->map_x] == '1') 
			break ;
		else
			{

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
	if (rc->side< 2)
		rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);



        // Calculate height of line to draw on screen (you need to implement your own height calculation logic)
        rc->line_height = (int)(SCREENHEIGHT / rc->perp_wall_dist);

        // Calculate lowest and highest pixel to fill in current stripe
        rc->draw_start = -rc->line_height / 2 + SCREENHEIGHT / 2;
        if (rc->draw_start < 0) 
		{
            rc->draw_start = 0;
        }
        rc->draw_end = rc->line_height / 2 + SCREENHEIGHT / 2;
        if (rc->draw_end >= SCREENHEIGHT) 
		{
            rc->draw_end = SCREENHEIGHT - 1;
        }

		//------------------------------------------------------------------

		y = rc->draw_start;

		while (y < rc->draw_end) 
		{
			unsigned int pixel_color;

			if(rc->side == 0)
				pixel_color = COLOR_NORTH;

			else if(rc->side == 1)
					pixel_color = COLOR_SOUTH;

			else if(rc->side == 2)
					pixel_color = COLOR_EAST;

			else if(rc->side == 3)
					pixel_color = COLOR_WEST;
			else
				pixel_color = 0;
			mlx_put_pixel(cube->cubmlx->img_buf, x, y, pixel_color);

			y++;
		}

		key_hook();
		//printf("dir x %f dir y %f plane x %f plane y %f\n",rc->dir_x,rc->dir_y,rc->plane_x,rc->plane_y);
		x++;
	}
	usleep(1000);
}	