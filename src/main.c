
#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		error("Error. Incorrect number of arguments");
	if (check_extension(argv[1]))
		error("Error. Incorrect map format");
	create_map(argv[1]);
	//launch game
	//mlx hook
	//cleanup
}
