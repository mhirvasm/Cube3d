# Executable name
NAME    = cub3d

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

#Includes
INCLUDES	= includes
IFLAGS		= -I$(INCLUDES) -I$(LIBFT_DIR)
LIBS        = -Llibft -lft

# Files
SRC     = src/main.c src/map.c src/map_utils.c src/utils.c src/cleanup.c
OBJ     = $(SRC:.c=.o)

# Libft
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

#Minilibx
MLX_DIR     := minilibx-linux
MLX_LIB     := $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS   := -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz

# Default
all: $(NAME)

# Main binary
$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(IFLAGS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Compile
%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -I$(MLX_DIR) -c $< -o $@

# Build libft via its own Makefile (won't relink unless lib changes)
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Build MLX so that lib exists (won't rebuild unless needed)
mlx: $(MLX_LIB)
$(MLX_LIB):
	@make -C $(MLX_DIR)

# Clean object files
clean:
	@make -C $(LIBFT_DIR) clean
	@make clean_mlx
	rm -f $(OBJ)

# Clean everything we own; MLX usually doesn’t have fclean, so call clean
fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Rebuild
re:
	@make fclean
	@make all

# Helper to clean MLX without failing if rule is missing
clean_mlx:
	@make -C $(MLX_DIR) clean

.PHONY: all clean fclean re
