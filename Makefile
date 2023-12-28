NAME = cub3D
MAP = "" 

INCLUDES = -I ./lib/libft/ -I ./lib/MLX42/include/MLX42/ -I ./ -I ./src/ -I ./include
SRCS = 	src/main.c \
		src/parse_colour.c\
		src/parse_map.c\
		src/parse_path.c\
		src/parse_verif.c\
		src/parsing.c \
		src/keyhook.c\
		src/errors.c \
		src/init.c\
		src/raycasting_set.c\
		src/raycasting.c\
		src/texture.c\
		src/mlx.c\
		src/gc.c\
		src/gc_split.c \
		src/gc_others.c \
		src/utils.c\

#	Directories
LIB_DIR = lib/
SRC_DIR	= src/
MAP_DIR = maps/
MLX_DIR = $(LIB_DIR)MLX42/
MLX_BUILD_DIR = $(MLX_DIR)build/
LIBFT_DIR = $(LIB_DIR)libft/

#	Libraries
LIBFT = $(LIBFT_DIR)libft.a
MLX42 = $(MLX_BUILD_DIR)libmlx42.a


CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -f

ifeq ($(shell uname), Linux)
	MLXFL = -Iinclude -ldl -lglfw -pthread -lm
else ifeq ($(shell uname), Darwin)
	MLXFL = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit #-fsanitize=address -g
endif

LIBS = $(MLX_DIR) $(LIBFT)

# 	Colors
CYAN = '\033[1;36m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
RESET_COLOR = '\033[0;0m'

all: $(NAME)

$(NAME): $(LIBS) $(SRCS) 
	@make -C $(MLX_BUILD_DIR)
	@$(CC) $(CFLAGS) $(SRCS) $(MLX42) $(LIBFT) $(MLXFL) $(INCLUDES) -o $(NAME)
	@ echo $(CYAN) cub3D created! $(RESET_COLOR)

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $(LIB_DIR)MLX42
	@(cd $(LIB_DIR)/MLX42 && cmake -B build && cmake --build build -j4)

$(LIBFT): 
	@$(MAKE) -C $(LIBFT_DIR)
				
clean: 
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo $(RED) object files deleted! $(RESET_COLOR)

mlx_clean:
	@if [ -d "$(MLX_DIR)" ]; then \
		make -C $(MLX_BUILD_DIR) clean; \
	fi
	@rm -rf $(MLX_DIR)
	
fclean: clean
	@$(MAKE) mlx_clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo $(RED) cub3D,libft.a and mlx files deleted! $(RESET_COLOR)

re: fclean all

leak: re
	@echo $(GREEN) Checking leaks ... $(RESET_COLOR)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes ./$(NAME) $(MAP_DIR)$(MAP)

run: all
	@echo $(GREEN) "Executing cub3d ..." $(RESET_COLOR)
	@./$(NAME) $(MAP_DIR)$(MAP)

.PHONY: all clean mlx_clean fclean re leak run
