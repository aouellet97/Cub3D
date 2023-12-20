#ifndef CUB3D_H
# define CUB3D_H

//	Headers ----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
# include <limits.h>

#include "libft.h"
# include "MLX42.h"

// 			- For Raycasting
# include <math.h>
# include "raycast.h"

# define SCREENWIDTH 1024
#define SCREENHEIGHT  768

//	Errors ----------------------------------------------------
#define ERROR -1
#define SUCESS 0

#define NOT_CUB "The file is not a .cub"
#define NO_MAP "Please pass one map as argument"

#define FD_ERROR "File does not exist or an error occured when oppening it"
#define MALLOC_ERROR "Error when allocating memory from heap"
#define READ_ERROR "Error when reading file"

#define MAP_NOT_END "Map is not at the end of the file"
#define WEIRD_CHAR "Map must contains only '0' '1' 'N' 'S' 'W' 'E' characters"  
#define MAP_OPEN "Playable map is not enclosed with walls or has holes on it"
#define MANY_POS "There's more than one player start position"
#define NO_POS "There is no player start position"
#define MAP_NOT "Map description not found"

#define NO_TEXT "Texture does not exist"
#define EXISTS "Element exists already"
#define BAD_COLOR "Error in the color code"
#define MORE_255 "Number higher than 255"
#define MISSING "Some informations are missing"
#define RANDOM "Random informations"


//	Colors ----------------------------------------------------
# define RED "\033[0;31m"
# define WHITE "\033[0;0m"
 
//	Buffer size ----------------------------------------------------
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define SPLIT_SEP 29

// ENUM
enum e_id
{
	NO,
	SO,
	EA,
	WE,
	C,
	F,
};  

enum e_ori
{
	N,
	S,
	E,
	W,
}; 

//	Structs ----------------------------------------------------

typedef struct s_mblock
{
	void			*address;
	struct s_mblock	*next_mb;
}	t_mblock;


typedef struct s_cubmlx
{
	mlx_t	*mlx;
	mlx_texture_t*	north_text;
	mlx_texture_t*	south_text;
	mlx_texture_t*	east_text;
	mlx_texture_t*	west_text;

	
}			t_cubmlx;


typedef struct s_raycast
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
}	t_raycast;

typedef struct s_cube
{
	int 	fd;
	char	*content;
	char	**tokens;
	char	**map;
	int 	y_size;
	int		x_size;
	int		width;
	int		height;
	enum 	e_ori orientation;
	int 	start_y;
	int		start_x;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		c_red;
	int		c_green;
	int		c_blue;
	int		f_red;
	int		f_green;
	int		f_blue;
	bool 	found_map;
	t_raycast *coordinates;	
	t_raycast *coords;
	t_cubmlx	*cubmlx;
}	t_cube;

t_cube	*get_cube();

//	Parsing ----------------------------------------------------
int	cub_verification(char *path);
void read_file(t_cube*cube);
void parsing(t_cube*cube);

//	Errors and free ----------------------------------------------------
void ft_error(char *message);

// Testing ------------------------------------------------
void print_tab(char**split);

// Raycasting ------------------------------------------------


// Mlx -------------------------------------------
int	ft_window(t_cube *cube);

// Garbage Collector and memory functions ------------------------------------------------
t_mblock	*garbage_collector(void);
void	*gc_malloc(size_t size);
void	gc_free_all(void);
void	gc_free(void*address);

char	*gc_substr(char const *s, unsigned int start, size_t len);
char	*gc_strdup(const char *s1);
char	*gc_strjoin(char const *s1, char const *s2);
char	**gc_split(char const *s, char c);
void	*gc_calloc(size_t nmemb, size_t size);
//test --
int test_ray(void);
void drawLineDDA(int x1, int y1, int x2, int y2);




#endif
