# Executable name
NAME    = cube3d

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

#Includes
INCS        := -I include -I libft
LIBS        := -Llibft -lft

# Files
SRC     = 
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
	$(CC) $(CFLAGS) -flto $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $@

# Compile
%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# Build libft via its own Makefile (won't relink unless lib changes)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Build MLX so that lib exists (won't rebuild unless needed)
mlx: $(MLX_LIB)
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

# Clean object files
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) clean_mlx
	rm -f $(OBJ)

# Clean everything we own; MLX usually doesn’t have fclean, so call clean
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Rebuild
re:
	$(MAKE) fclean
	$(MAKE) all

# Helper to clean MLX without failing if rule is missing
clean_mlx:
	-$(MAKE) -C $(MLX_DIR) clean

.PHONY: all clean fclean re