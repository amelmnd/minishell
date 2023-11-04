#include "minishell.h"

void	print_charss(char **str_array)
{
	int	i = -1;

	while (str_array[++i])
		printf("%s\n", str_array[i]);
}