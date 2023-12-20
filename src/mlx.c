// #include "cub3d.h"

// static void	ft_mchook(mlx_key_data_t k, void *param)
// {
// 	t_map	*gpack;
// 	int		move;

// 	gpack = param;
// 	if (k.key == MLX_KEY_D && k.action == 1)
// 		move = 'R';
// 	if (k.key == MLX_KEY_A && k.action == 1)
// 		move = 'L';
// 	if (k.key == MLX_KEY_W && k.action == 1)
// 		move = 'U';
// 	if (k.key == MLX_KEY_S && k.action == 1)
// 		move = 'D';
// 	if (move && k.action == 1)
// 		;
// 	if (k.key == MLX_KEY_ESCAPE && k.action == 1)
// 	{
// 		mlx_terminate(gpack->mlx);
// 		// leave(gpack);
// 	}
// }



// static void init_map(t_map *gpack)
// {
// 	//Mem allocated
// 	int what[8][8]	= 
// 	{
//     {'1', '1', '1', '1', '1', '1', '1', '1'},
//     {'1', '0', '0', '0', '0', '0', '0', '1'},
//     {'1', '0', '1', '1', '1', '1', '0', '1'},
//     {'1', '0', '1', '0', '0', '1', '0', '1'},
//     {'1', '0', '1', '0', '0', '1', '0', '1'},
//     {'1', '0', '0', '0', '0', '0', '0', '1'},
//     {'1', '1', '1', '1', '1', '1', '1', '1'},
//     {'1', '1', '1', '1', '1', '1', '1', '1'}
// 	};
// 	// gpack->map = what;
// }





int	ft_window(t_cube *gpack)
{
	gpack->setup->mlx = mlx_init(gpack->x_size * 64, gpack->y_size * 64,
			"CUB3D by TDA-3D", 1);
	if (!gpack->setup->mlx)
		;
	// init_map(gpack);
	//mlx_key_hook(gpack->mlx, &ft_mchook, gpack);
	mlx_loop(gpack->setup->mlx);
	mlx_terminate(gpack->setup->mlx);
	// mlx_put_pixel();
	// leave(gpack);
	return (1);
}



