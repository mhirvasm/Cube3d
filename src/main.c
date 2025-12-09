
#include "cub3d.h"

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
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	//init mlx
	//launch game
	//mlx hook
	//cleanup
}
