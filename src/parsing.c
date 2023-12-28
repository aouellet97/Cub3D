#include "cub3d.h"

void	read_file(t_cube *cube)
{
	char	*buffer;
	char	*copy;

	int read_return ;
	buffer = NULL;
	copy = NULL;
	read_return = 0;
	buffer = gc_calloc(sizeof(char), BUFFER_SIZE + 1);
	while (1)
	{
		read_return = read(cube->fd, buffer, BUFFER_SIZE);
		if (read_return == ERROR)
			ft_error(READ_ERROR);
		if (read_return == 0)
			break ;
		copy = cube->content;
		cube->content = gc_strjoin(copy, buffer);
		ft_bzero(buffer, BUFFER_SIZE + 1);
	}
}

char	*remove_wspaces(char *line)
{
	char	**split;
	char	*copy;
	int		i;

	i = 0;
	copy = NULL;
	split = NULL;
	while (line[i])
	{
		if (is_whitespace(line[i]) == 1)
			line[i] = SPLIT_SEP;
		i++;
	}
	split = gc_split(line, SPLIT_SEP);
	line = NULL;
	i = 0;
	while (split && split[i])
	{
		copy = line;
		line = gc_strjoin(copy, split[i]);
		i++;
	}
	return (line);
}

void	loop_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_whitespace(line[i]) == true)
		i++;
	if (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			get_cube()->found_map = true;
		else if (line[i] == 'N' && line[i + 1] == 'O')
			add_path(remove_wspaces(line) + 2, NO);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			add_path(remove_wspaces(line) + 2, SO);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			add_path(remove_wspaces(line) + 2, EA);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			add_path(remove_wspaces(line) + 2, WE);
		else if (line[i] == 'C')
			parse_color_code(remove_wspaces(line) + 1, C);
		else if (line[i] == 'F')
			parse_color_code(remove_wspaces(line) + 1, F);
		else
			ft_error(RANDOM);
	}
}

void	tokens_loop(char **tokens)
{
	t_cube	*cube;
	int		i;

	cube = get_cube();
	cube->found_map = false;
	i = 0;
	while (tokens[i])
	{
		loop_line(tokens[i]);
		if (cube->found_map == true)
			break ;
		i++;
	}
	if (!cube->no_path || !cube->so_path || !cube->ea_path || !cube->we_path
		|| cube->c_red == -1 || cube->c_green == -1 || cube->c_blue == -1
		|| cube->f_red == -1 || cube->f_green == -1 || cube->f_blue == -1)
		ft_error(MAP_NOT_END);
	if (cube->found_map == false)
		ft_error(MAP_NOT);
}

void	parsing(t_cube *cube)
{
	char	*map_content;

	map_content = NULL;
	init_infos(cube);
	cube->tokens = gc_split(cube->content, '\n');
	tokens_loop(cube->tokens);
	map_content = cube->content + find_map_start(cube->content);
	validate_map(map_content);
	cube->map = get_map(cube, map_content);
	find_position(cube->map, cube, 0, 0);
	flood_fill(cube, cube->start_y, cube->start_x);
	print_tab(cube->map);
}

//integrate garbage collector and copy libft mallocedfunctions here

//dont forget to check if map is not bigger than screen size