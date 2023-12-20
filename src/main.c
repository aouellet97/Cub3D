#include "cub3d.h"

t_cube	*get_cube()
{
	static t_cubmlx cubmlx;
	static t_cube cube;
	cube.cubmlx = &cubmlx;

	return (&cube);
}

	 		  	 	 	 	 	 	 	

void print_tab(char**split)
{
	int i = 0;
	if(!split)
		return ;
	while(split[i])
	{
		printf("%s\n",split[i]);
		i++;
	}
}


int main(int argc, char **argv)
{ 
	t_cube* cube;

	cube = get_cube();
	if(argc < 2)
		ft_error(NO_MAP);
	if(cub_verification(argv[1]) == ERROR)
		ft_error(NOT_CUB);     
	cube->fd = open(argv[1], O_RDONLY);
	if(cube->fd == ERROR)
		ft_error(FD_ERROR);
	read_file(cube);
	parsing(get_cube());
	ft_window(cube);
	gc_free_all();
	return SUCESS; 
}