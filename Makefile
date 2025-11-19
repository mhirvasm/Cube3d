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

# Default
all: $(NAME)

# Link
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCS) $(LIBS) -o $@

# Compile
%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re