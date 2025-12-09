
#include "cub3d.h"

int	check_extension(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (!(arg[len - 1] == 'b' && arg[len - 2] == 'u' && arg[len - 3] == 'c'
		&& arg[len - 4] == '.'))
		return (1);
	return (0);
}
