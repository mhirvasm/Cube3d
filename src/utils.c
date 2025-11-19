
#include "cub3d.h"

int	check_extension(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (!(arg[len] == 'b' && arg[len - 1] == 'u' && arg[len - 2] == 'c'
		&& arg[len - 3] == '.'))
		return (1);
	return (0);
}
