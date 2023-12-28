#ifndef CUB3D_H
# define CUB3D_H

//	Headers ----------------------------------------------------
# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// 			- For Raycasting
# include "raycast.h"
# include <math.h>

# define SCREENWIDTH 1080
# define SCREENHEIGHT 720
# define TEXWIDTH 64
# define TEXTHEIGHT 64

# define MOVE_SPEED 0.00008
# define ROTATE_SPEED 0.00007

# define ROTATE_RIGHT 1
# define ROTATE_LEFT 2
# define MOVE_UP 1
# define MOVE_DOWN 2
# define MOVE_LEFT 3
# define MOVE_RIGHT 4
//	Errors ----------------------------------------------------
# define ERROR -1
# define SUCESS 0

# define NOT_CUB "The file is not a .cub"
# define NOT_PNG "THe texture is not a .png"
# define NO_MAP "Please pass one map as argument"

# define FD_ERROR "File does not exist or an error occured when oppening it"
# define MALLOC_ERROR "Error when allocating memory from heap"
# define READ_ERROR "Error when reading file"

# define MAP_NOT_END "Map is not at the end of the file"
# define WEIRD_CHAR "Map must contains only '0' '1' 'N' 'S' 'W' 'E' characters"
# define MAP_OPEN "Playable map is not enclosed with walls or has holes on it"
# define MANY_POS "There's more than one player start position"
# define NO_POS "There is no player start position"
# define MAP_NOT "Map description not found"

# define NO_TEXT "Texture does not exist"
# define EXISTS "Element exists already"
# define BAD_COLOR "Error in the color code"
# define MORE_255 "Number higher than 255"
# define MISSING "Some informations are missing"
# define RANDOM "Random informations"

# define MLXER "mlx failed in some way"

//	Colors ----------------------------------------------------
# define RED "\033[0;31m"
# define WHITE "\033[0;0m"

//	Buffer size ----------------------------------------------------
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define SPLIT_SEP 29

// ENUM
enum				e_id
{
	NO,
	SO,
	EA,
	WE,
	C,
	F,
};

enum				e_dir
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
}					t_mblock;

typedef struct s_cubmlx
{
	mlx_t			*mlx;
	mlx_texture_t	*north_text;
	mlx_texture_t	*south_text;
	mlx_texture_t	*east_text;
	mlx_texture_t	*west_text;

	uint32_t		**n_buffer;
	uint32_t		**s_buffer;
	uint32_t		**e_buffer;
	uint32_t		**w_buffer;

	mlx_image_t		*img_buf;
	uint32_t		ceiling_color;
	uint32_t		floor_color;

}					t_cubmlx;

typedef struct s_raycast
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			camera_x;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			step_x;
	double			step_y;
	double			side_dist_x;
	double			side_dist_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			new_x;
	double			new_y;
}					t_raycast;

typedef struct s_cube
{
	int				fd;
	char			*content;
	char			**tokens;
	char			**map;
	int				y_size;
	int				x_size;
	int				width;
	int				height;
	enum e_dir		orientation;
	int				start_y;
	int				start_x;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				c_red;
	int				c_green;
	int				c_blue;
	int				f_red;
	int				f_green;
	int				f_blue;
	bool			found_map;
	t_raycast		*raycast;
	t_cubmlx		*cubmlx;
}					t_cube;

t_cube				*get_cube(void);
// Init ----------------------------------
void				init_infos(t_cube *cube);
void				get_map_infos(t_cube *cube, char *content);
char				**get_map(t_cube *cube, char *content);
// Parse_colour ----------------------------
void				add_color_code(enum e_id id, int n, int i);
void				split_color_code(char *code, enum e_id id);
void				parse_color_code(char *code, enum e_id id);
// Parse_map ---------------------------------
int					find_map_start(char *content);
void				validate_map(char *content);
void				flood_fill(t_cube *cube, int y, int x);
// Parse_path -------------------------------
void				add_path_body(t_cube *cube, char *path, enum e_id id);
void				add_path(char *path, enum e_id id);
// Parse_verif ----------------------------------------
int					cub_verification(char *path);
int					png_verification(char *path);
//	Parsing ----------------------------------------------------
void				read_file(t_cube *cube);
void				parsing(t_cube *cube);
// Keyhook --------------------------------
void				key_hook(t_cube *cube, t_raycast *rc);
//	Errors and free ----------------------------------------------------
void				ft_error(char *message);
void				clear_mlx(t_cubmlx *cmlx);
// Testing ------------------------------------------------
void				print_tab(char **split);
// Raycasting ------------------------------------------------
void				raycasting_loop(void *arg);
// Raycasting_set ----------------------------------
void				set_vars_raycast(t_cube *cube, t_raycast *rc);
void				set_raycast_vars(t_raycast *rc);
// Texture ---------------------------
void				cast_floor_ceiling(int x, int y, t_raycast *rc);
void				display_texture(t_cube *cube, int x);
// Mlx -------------------------------------------
void				mlx_start(t_cube *cube);
// Garbage Collector and memory functions ---------------------------------
t_mblock			*garbage_collector(void);
void				*gc_malloc(size_t size);
void				gc_free_all(void);
void				gc_free(void *address);

char				*gc_substr(char const *s, unsigned int start, size_t len);
char				*gc_strdup(const char *s1);
char				*gc_strjoin(char const *s1, char const *s2);
char				**gc_split(char const *s, char c);
void				*gc_calloc(size_t nmemb, size_t size);
// Utils ------------------------------------------------------------
int					is_whitespace(char c);
int					is_map_char(char c);
void				find_position(char **map, t_cube *cube, int x, int y);
#endif
