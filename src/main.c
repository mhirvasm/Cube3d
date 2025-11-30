
#include "cub3d.h"

static int	key_handler(int keycode, t_game *game) //Temp  for testing
{
	if (keycode == KEY_ESC)
		error_and_exit("Game closed", game); 
	return (0);
}

static int	close_window(t_game *game) //temp for testing
{
	error_and_exit("Game closed", game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game)); //init struct here 
	if (argc != 2)
		error("Error. Incorrect number of arguments");
	if (check_extension(argv[1]))
		error("Error. Incorrect map format");
	if (init_game(&game, argv[1]) != 0)
		error("Error. Initialization failed");
	//create_map(argv[1]); <-- instead of this, lets do init game function which calls this
	//init mlx
	//launch game
	//mlx hook
	//cleanup
}
