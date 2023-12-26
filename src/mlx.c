#include "cub3d.h"

int	translate_color(int r, int g, int b, int alpha)
{
	return (r << 24 | g << 16 | b << 8 | alpha);
}






void texture_buffer(mlx_texture_t *texture, uint32_t **buffer)
{
	uint32_t	x;
	uint32_t y;
	uint32_t i;

	y = 0;
	x = 0;
	i = 0;
	buffer = gc_malloc(sizeof(uint32_t *) * (texture->height + 1) );
	while (x < texture->height)
	{
		buffer[x] = gc_malloc( sizeof(uint32_t) * (texture->width));
		x++;
	}
	while (y < texture->height - 1)
	{
		x = 0;
		while (x < texture->width)
		{
			buffer[y][x] = translate_color((uint32_t)texture->pixels[i], (uint32_t)texture->pixels[i + 1],
			 (uint32_t)texture->pixels[i + 2], (uint32_t)texture->pixels[i + 3]);
			i += 4;
			x++;
		}
		y++;
	}
}

void  display_background(t_cube *cube)
{
	int x;
	int y;

	y = 0;
	x = 0;
	while(y < SCREENHEIGHT / 2)
	{
		x = 0;
		while(x < SCREENWIDTH)
		{
			mlx_put_pixel(cube->cubmlx->bg_buf,x,y,cube->cubmlx->floor_color);
			x++;
		}
		y++;
	}
	while(y < SCREENHEIGHT)
	{
		x = 0;
		while(x < SCREENWIDTH)
		{
			mlx_put_pixel(cube->cubmlx->bg_buf,x,y,cube->cubmlx->ceiling_color);
			x++;
		}
		y++;
	}
}




int	mlx_start(t_cube *cube)
{
	cube->cubmlx->ceiling_color = translate_color(cube->c_red, cube->c_green, cube->c_blue, 255);
	cube->cubmlx->floor_color = translate_color(cube->f_red, cube->f_green, cube->f_blue, 255);
	cube->cubmlx->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "CUB3D by TDA-3D", false);
	if(!cube->cubmlx->mlx)
		return 1; 

	cube->cubmlx->bg_buf = mlx_new_image(cube->cubmlx->mlx,SCREENWIDTH,SCREENHEIGHT);
	if(!cube->cubmlx->bg_buf)
		return 1;
	display_background(cube);
	if(mlx_image_to_window(cube->cubmlx->mlx,cube->cubmlx->bg_buf,0,0) == ERROR)
		return 1;

	cube->cubmlx->img_buf = mlx_new_image(cube->cubmlx->mlx,SCREENWIDTH,SCREENHEIGHT);
	if(!cube->cubmlx->img_buf)
		return 1;
	if(mlx_image_to_window(cube->cubmlx->mlx,cube->cubmlx->img_buf,0,0) == ERROR)
		return 1;

	cube->cubmlx->south_text = mlx_load_png(cube->so_path);
	if(!cube->cubmlx->south_text)
		return 1;

	 cube->cubmlx->north_text = mlx_load_png(cube->no_path);
	 if(!cube->cubmlx->north_text)
	 	return 1;
	 cube->cubmlx->east_text = mlx_load_png(cube->ea_path);
	 if(!cube->cubmlx->east_text)
	 	return 1;
	 cube->cubmlx->west_text = mlx_load_png(cube->we_path);
	 if(!cube->cubmlx->west_text)
	 	return 1;
	texture_buffer(cube->cubmlx->north_text, cube->cubmlx->n_buffer);
	texture_buffer(cube->cubmlx->south_text, cube->cubmlx->s_buffer);
	texture_buffer(cube->cubmlx->east_text, cube->cubmlx->e_buffer);
	texture_buffer(cube->cubmlx->west_text, cube->cubmlx->w_buffer);
	set_raycast_vars(cube->raycast);

	//mlx_key_hook(cube->cubmlx->mlx, &key_hook, NULL);
	mlx_loop_hook(cube->cubmlx->mlx,&raycasting_loop,cube);
	mlx_loop(cube->cubmlx->mlx);
	mlx_terminate(cube->cubmlx->mlx);
	//free mlx stuff and add in error function
	return (EXIT_SUCCESS);
}
