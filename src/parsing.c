#include "cub3d.h"

int	cub_verification(char *path)
{
	int	len;
         
	len = ft_strlen(path);
	if (len > 4 && path[len - 5] != '/' && ft_tolower(path[len - 1]) == 'b' && 
		ft_tolower(path[len- 2]) == 'u' && ft_tolower(path[len - 3]) == 'c' && path[len - 4] == '.')
		return (SUCESS);
	return (ERROR);
} 

void read_file(t_cube*cube)
{
	int read_return;
	char *buffer;
	char *copy;

	buffer = NULL;
	copy = NULL;
	read_return = 0;
	buffer = gc_calloc(sizeof(char),BUFFER_SIZE + 1); 
	while(1) 
	{
		read_return = read(cube->fd, buffer, BUFFER_SIZE);
		if(read_return == ERROR)
			ft_error(READ_ERROR);
		if(read_return == 0)
			break;
		copy = cube->content;
		cube->content  = gc_strjoin(copy, buffer);
		ft_bzero(buffer,BUFFER_SIZE+1);
	}
}

int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int is_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N'
	|| c == 'S' || c == 'W' || c == 'E');
}


char	*remove_wspaces(char *line)
{
	char	**split;
	char	*copy;
	int i;
	
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
void add_path_body(t_cube *cube, char *path, enum e_id id)
{
	if(id == NO)
	{
		if(cube->no_path)
			ft_error(EXISTS);
		cube->no_path = path;
	}
	if(id == SO)
	{
		if(cube->so_path)
			ft_error(EXISTS);
		cube->so_path = path;
	}
	if(id == EA)
	{
		if(cube->ea_path)
			ft_error(EXISTS);
		cube->ea_path = path;
	}
	if(id == WE)
	{
		if(cube->we_path) 
			ft_error(EXISTS);
		cube->we_path = path;
	}
}

void add_path( char *path, enum e_id id)
{
	t_cube *cube;
	
	cube = get_cube();
	if(access(path, R_OK) != 0)
		ft_error(NO_TEXT);
	add_path_body(cube, path, id);
}

void add_color_code(enum e_id id, int n, int i)
{
	t_cube *cube;
	
	cube = get_cube();
	if(id == C)
	{
		if(i == 0)	
			cube->c_red = n;
		if(i == 1)	
			cube->c_green = n;
		if(i == 2)	
			cube->c_blue = n;	
	}
	if(id == F)
	{
		if(i == 0)	
			cube->f_red = n;
		if(i == 1)	
			cube->f_green = n;
		if(i == 2)	
			cube->f_blue = n;	
	}
}
void split_color_code(char *code, enum e_id id)
{
	char **split;
	int i;
	int n;

	n = 0;
	i = 0;
	split = gc_split(code, ',');
	while(split[i])
	{
		n = ft_atoi(split[i]);
		if(n > 255)
			ft_error(MORE_255);
		add_color_code(id,n,i); 
		i++;
	}										
	if(i != 3)
		ft_error(BAD_COLOR);
}

void parse_color_code(char *code, enum e_id id)
{
	static int c_count = 0;
	static int f_count = 0;
	int i;
	
	i = 0;
	if(id == C)
		c_count++;
	if(id == F)
		f_count++;
	if(c_count > 1 || f_count > 1)
		ft_error(EXISTS);
	while(code[i] && ft_isdigit(code[i]) == true)
		i++;
	if(code[i] == ',')
		i++;
	while(code[i] && ft_isdigit(code[i]) == true)
		i++;
	if(code[i] == ',')
		i++;
	while(code[i] && ft_isdigit(code[i]) == true)
		i++;
	if(code[i])
		ft_error(BAD_COLOR);
	split_color_code(code, id);
}

void loop_line(char *line)
{
	int i;

	i = 0;
	while(line[i] && is_whitespace(line[i]) == true)
		i++;
	if(line[i])
	{
		if(line[i] == '1' || line[i] == '0')
			get_cube()->found_map = true;
		else if(line[i] == 'N' && line[i + 1] == 'O')
			add_path(remove_wspaces(line) + 2, NO);
		else if(line[i] == 'S' && line[i + 1] == 'O')
			add_path(remove_wspaces(line) + 2, SO);
		else if(line[i] == 'E' && line[i + 1] == 'A')
			add_path(remove_wspaces(line) + 2, EA);
		else if(line[i] == 'W' && line[i + 1] == 'E')
			add_path(remove_wspaces(line) + 2, WE);
		else if(line[i] == 'C')
			parse_color_code(remove_wspaces(line) + 1, C);
		else if(line[i] == 'F')
			parse_color_code(remove_wspaces(line) + 1, F);
		else
		 	ft_error(RANDOM);
	}
}

int find_map_start(char *content)
{
	int i;
	int start;

	i = 0;
	start = 0;
	while(content[i])
	{
		if(content[i] == '\n')
		{
			i++;
			start = i;
			while(content[i] && is_whitespace(content[i]) == true && content[i] != 10)
				i++;
			if(content[i] == '0' || content[i] == '1')
				return start; 
		}
		else
			i++;
	}
	return -1;
}

void validate_map(char *content)
{
	static int count = 0;
	int i;

	i = 0;
	while(content[i]) 
	{
		if(content[i] == 'N'|| content[i]  == 'S' 
			|| content[i]  == 'W' || content[i]  == 'E')
			count++;
		if(count > 1)
			ft_error(MANY_POS);
		if(is_whitespace(content[i]) == false && (content[i] != '1' && content[i] != '0' 
		&& content[i] != 'N' && content[i] != 'S' && content[i]  != 'W' && content[i] != 'E'))
			ft_error(WEIRD_CHAR);
		i++;
	}
	if(count == 0)
		ft_error(NO_POS);
}

void tokens_loop(char **tokens)
{
	t_cube *cube;
	int i;
	
	cube = get_cube();
	cube->found_map = false;
	i = 0;
	while(tokens[i])
	{
		loop_line(tokens[i]);
		if(cube->found_map == true)
			break ;
		i++;
	}
	if(!cube->no_path || !cube->so_path || !cube->ea_path 
		|| !cube->we_path || cube->c_red == -1 || cube->c_green == -1 
		|| cube->c_blue == -1 || cube->f_red == -1 || cube->f_green == -1 
		|| cube->f_blue == -1)
		ft_error(MAP_NOT_END);
	if(cube->found_map == false)
		ft_error(MAP_NOT);
}
void get_map_infos(t_cube* cube, char *content)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while(content[i])
	{
		len = 0;
		while(content[i] && content[i] != '\n')
		{
			if(content[i] == '\t')
				len += 3 - ((len  ) % 4);
			len++;
			i++;
		}
		if(content[i] == '\n')
			cube->y_size++;
		if(len > cube->x_size)
			cube->x_size = len;
		if(content[i])
			i++;
	}
}

void populate_map(char**map, char *content)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while(content[i])
	{
		j = 0;
		while(content[i] && content[i] != '\n')
		{
			if(content[i] == '\t')
				j += (4 - ((j) % 4) -1 ); 
			if(is_whitespace(content[i]) == false)
				map[k][j] = content[i];
			j++;
			i++;
		}
		if(content[i] == '\n')
			k++;
		if(content[i])
			i++;
	}
}

char** get_map(t_cube* cube, char *content)
{
	char **map;
	int i;

	i = 0;
	map = NULL;
	cube->y_size = 0;
	cube->x_size = 0;
	get_map_infos(cube, content);
	map = gc_malloc(sizeof(char*) * (cube->y_size + 2));
	map[cube->y_size + 1] = NULL;
	i = 0;
	while(i < cube->y_size + 1)
	{
		map[i] = gc_malloc(sizeof(char) * (cube->x_size + 1));
		map[i][cube->x_size] = 0;
		ft_memset(map[i],'-', cube->x_size);//change with space
		i++;
	}
	populate_map(map, content);
	cube->height = cube->y_size + 1;
	cube->width = cube->x_size;
	return map;
}

void flood_fill(t_cube *cube, int y, int x)
{
	if(cube->map[y][x] == '-' || x == 0 || y == 0 || x == get_cube()->x_size - 1
		|| y == get_cube()->y_size )//change to space
		ft_error(MAP_OPEN);
	if(cube->map[y][x] == '0')
		cube->map[y][x] = 'X';
	if(cube->map[y][x + 1] && cube->map[y][x + 1] != '1' && cube->map[y][x + 1] != 'X')
		flood_fill(cube,y,x+1);
	if(cube->map[y][x - 1] && cube->map[y][x - 1]!= '1' && cube->map[y][x - 1] != 'X')
		flood_fill(cube,y,x-1);
	if(cube->map[y + 1] && cube->map[y + 1][x] != '1' && cube->map[y + 1][x] != 'X')
		flood_fill(cube,y + 1,x);
	if(cube->map[y - 1] && cube->map[y - 1][x] != '1' && cube->map[y - 1][x] != 'X')
		flood_fill(cube,y - 1,x);
	
}

void find_position(char **map,t_cube *cube, int x, int y)
{
	while(map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if(is_map_char(map[y][x]) == true && map[y][x] != '1'
			&& map[y][x] != '0')
			{
				if(map[y][x] == 'N')
					cube->orientation = N;
				if(map[y][x] == 'S')
					cube->orientation = S;
				if(map[y][x] == 'E')
					cube->orientation = E;
				if(map[y][x] == 'W')
					cube->orientation = W;
				cube->start_x = x;
				cube->start_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void init_infos(t_cube*cube)
{
	cube->no_path = NULL;
	cube->so_path = NULL;
	cube->ea_path = NULL;
	cube->we_path = NULL;
	cube->c_red = -1;
	cube->c_green = -1;
	cube->c_blue = -1;
	cube->f_red = -1;
	cube->f_green = -1; 
	cube->f_blue = -1;
}

void parsing(t_cube*cube)
{
	char *map_content;

	map_content = NULL;
	init_infos(cube);
	
	cube->tokens = gc_split(cube->content,'\n');
	tokens_loop(cube->tokens);
	map_content = cube->content + find_map_start(cube->content);
	validate_map(map_content);
	cube->map = get_map(cube, map_content);
	find_position(cube->map, cube, 0 ,0);
	flood_fill(cube,cube->start_y,cube->start_x);
	print_tab(cube->map);
}

//integrate garbage collector and copy libft mallocedfunctions here

//dont forget to check if map is not bigger than screen size