#include "cub3d.h"

static int	translate_color(int r, int g, int b, int alpha)
{
	return (r << 24 | g << 16 | b << 8 | alpha);
}

static uint32_t	line_saver(uint32_t i, uint32_t x)
{
	(void)x;
	return (i + 4);
}

static uint32_t	**texture_buffer(mlx_texture_t *texture)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;
	uint32_t	**buffer;

	y = 0;
	x = 0;
	i = 0;
	buffer = gc_malloc(sizeof(uint32_t *) * (texture->height + 1));
	while (x < texture->height)
		buffer[x++] = gc_malloc(sizeof(uint32_t) * (texture->width));
	while (y < texture->height - 1)
	{
		x = 0;
		while (x < texture->width)
		{
			buffer[y][x] = translate_color((uint32_t)texture->pixels[i],
					(uint32_t)texture->pixels[i + 1],
					(uint32_t)texture->pixels[i + 2],
					(uint32_t)texture->pixels[i + 3]);
			i = line_saver(i, x++);
		}
		y++;
	}
	return (buffer);
}

static void	init_image(t_cube *cube)
{
	if (mlx_image_to_window(cube->cubmlx->mlx, cube->cubmlx->img_buf, 0,
			0) == ERROR)
		ft_error(MLXER);
	cube->cubmlx->south_text = mlx_load_png(cube->so_path);
	if (!cube->cubmlx->south_text)
		ft_error(MLXER);
	cube->cubmlx->north_text = mlx_load_png(cube->no_path);
	if (!cube->cubmlx->north_text)
		ft_error(MLXER);
	cube->cubmlx->east_text = mlx_load_png(cube->ea_path);
	if (!cube->cubmlx->east_text)
		ft_error(MLXER);
	cube->cubmlx->west_text = mlx_load_png(cube->we_path);
	if (!cube->cubmlx->west_text)
		ft_error(MLXER);
}

void	mlx_start(t_cube *cube)
{
	cube->cubmlx->ceiling_color = translate_color(cube->c_red, cube->c_green,
			cube->c_blue, 255);
	cube->cubmlx->floor_color = translate_color(cube->f_red, cube->f_green,
			cube->f_blue, 255);
	cube->cubmlx->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "CUB3D by TDA-3D",
			false);
	if (!cube->cubmlx->mlx)
		ft_error(MLXER);
	cube->cubmlx->img_buf = mlx_new_image(cube->cubmlx->mlx, SCREENWIDTH,
			SCREENHEIGHT);
	if (!cube->cubmlx->img_buf)
		ft_error(MLXER);
	init_image(cube);
	cube->cubmlx->n_buffer = texture_buffer(cube->cubmlx->north_text);
	cube->cubmlx->s_buffer = texture_buffer(cube->cubmlx->south_text);
	cube->cubmlx->e_buffer = texture_buffer(cube->cubmlx->east_text);
	cube->cubmlx->w_buffer = texture_buffer(cube->cubmlx->west_text);
	set_raycast_vars(cube->raycast);
	mlx_loop_hook(cube->cubmlx->mlx, &raycasting_loop, cube);
	mlx_loop(cube->cubmlx->mlx);
}
