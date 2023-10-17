#include "minishell.h"

t_exec_list *new_exec_list_node(void)
{
	t_exec_list *new = NULL;

	new = (t_exec_list *)malloc(sizeof(t_exec_list));
	if (!new)
		return (NULL);
	return (new);
}

void	init_exec_list(t_msh *msh)
{
	msh->exec_list->arg_array = NULL;
	msh->exec_list->cmd = NULL;
	msh->exec_list->next = NULL;
	msh->exec_list->previous = NULL;
	msh->exec_list->redirect_array = NULL;
}

void	init_exec_list_node(t_exec_list *exec_list_node)
{
	exec_list_node->arg_array = NULL;
	exec_list_node->cmd = NULL;
	exec_list_node->next = NULL;
	exec_list_node->previous = NULL;
	exec_list_node->redirect_array = NULL;
}

void	plug_exec_list_node(t_msh *msh, t_exec_list *exec_list_node)
{
	t_exec_list *exec_list_i = msh->exec_list;

	while (exec_list_i->next)
		exec_list_i = exec_list_i->next;
	exec_list_i->next = exec_list_node;
	exec_list_node->previous = exec_list_i;
}


int	get_nb_pipes_in_exp_list(t_msh *msh)
{
	int	nb_pipes = 0;
	t_exp_list	*exp_list_node = msh->exp_list;

	while (exp_list_node)
	{
		if (exp_list_node->exp_type == PIPE_EXPANDED)
			nb_pipes++;
		exp_list_node = exp_list_node->next;
	}
	return (nb_pipes);
}

void	create_and_plug_all_empty_exec_list_nodes(t_msh *msh, int nb_pipes)
{
	int	i = -1;
	t_exec_list	*exec_list_node = NULL;

	while (++i < nb_pipes)
	{
		exec_list_node = new_exec_list_node();
		init_exec_list_node(exec_list_node);
		plug_exec_list_node(exec_list_node);
	}
}

void	print_exec_list(t_msh *msh)
{

}


void	build_exec_list(t_msh *msh)
{
	int	nb_pipes = 0;

	msh->exec_list = new_exec_list_node();
	init_exec_list(msh);
	nb_pipes = get_nb_pipes_in_exp_list(msh);
	create_and_plug_all_empty_exec_list_nodes(msh, nb_pipes);
}
