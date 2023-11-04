#include "minishell.h"

void	free_chars(char **dust)
{
	if (*dust)
	{
		free(*dust);
		*dust = NULL;
	}
}
