#include "minishell.h"

t_exec	*new_exec(void)
{
	t_exec	*new;

	new = NULL;
	new = (t_exec *)malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	return (new);
}
