
#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		error_and_exit("Error. Incorrect number of arguments\n");
	if (check_extension(argv[1]);
		error_and_exit("Error. Incorrect map format\n");
	create_map(argv[1]);
	//launch game
	//mlx hook
	//cleanup
}
