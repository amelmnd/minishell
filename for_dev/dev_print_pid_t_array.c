// à supprimer à terme
// à intégrer à un dev.h pour le moment peut-être ?

#include "minishell.h"

void	print_pid_t_array(t_msh *msh)
{
	int	size_pid_t_array;
	int	i;

	if (msh && msh->exec && msh->exec_list)
	{
		size_pid_t_array = msh->exec_list->nb_pipes + 1;
		i = -1;
		while (++i < size_pid_t_array)
			dprintf(2, "[%d] ", msh->exec->pid_t_array[i]);
		dprintf(2, "\n");
	}
}