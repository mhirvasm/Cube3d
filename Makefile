# Executable name
NAME    = cube3d

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

# Files
SRC     = 
OBJ     = $(SRC:.c=.o)

# Default
all: $(NAME)

# Link
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Compile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Full clean
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re