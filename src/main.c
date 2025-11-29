
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game)); //init struct here 
	if (argc != 2)
		error("Error. Incorrect number of arguments");
	if (check_extension(argv[1]))
		error("Error. Incorrect map format");
	if (init_game(&game, argv[1] != 0))
		error("Error. Initialization failed");
	//create_map(argv[1]); <-- instead of this, lets do init game function which calls this
	//init mlx
	//launch game
	//mlx hook
	//cleanup
}
