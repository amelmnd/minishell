#include "minishell.h"

void	print_charss(char **str_array)
{
	int	i = -1;

	while (str_array[++i])
		dprintf(2, "%s\n", str_array[i]);
}