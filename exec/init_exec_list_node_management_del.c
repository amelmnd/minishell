#include "minishell.h"

t_exec_list *new_exec_list_node(void)
{
	t_exec_list *new = NULL;

	new = (t_exec_list *)malloc(sizeof(t_exec_list));
	if (!new)
		return (NULL);
	return (new);
}

void	init_exec_list_node(t_exec_list *exec_list_node)
{
	exec_list_node->next = NULL;
	exec_list_node->previous = NULL;
	exec_list_node->redirect_array = NULL;
	exec_list_node->nb_redirects = 0;
	exec_list_node->cmd = NULL;
	exec_list_node->args_array = NULL;
	exec_list_node->nb_words = 0;
	exec_list_node->next_pipe = 0;
	exec_list_node->nb_pipes = 0;
	exec_list_node->hd_pipe[READ] = -1;
	exec_list_node->hd_pipe[WRITE] = -1;
	exec_list_node->contains_hd = FALSE;
	exec_list_node->pos_ppl = INIT_POS_PPL_VALUE;
	exec_list_node->contains_write_redirect = FALSE;
	exec_list_node->hd = NULL;
}

void	plug_exec_list_node(t_msh *msh, t_exec_list *exec_list_node)
{
	t_exec_list *exec_list_i = msh->exec_list;

	while (exec_list_i->next)
		exec_list_i = exec_list_i->next;
	exec_list_i->next = exec_list_node;
	exec_list_node->previous = exec_list_i;
}

void	create_and_plug_all_empty_exec_list_nodes(t_msh *msh)
{
	int	i = -1;
	int	nb_pipes = msh->exec_list->nb_pipes;
	t_exec_list	*exec_list_node = NULL;

	while (++i < nb_pipes) // sachant qu'il y a déjà un node initial, le compte est bon
	{
		exec_list_node = new_exec_list_node();
		init_exec_list_node(exec_list_node);
		exec_list_node->nb_pipes = msh->exec_list->nb_pipes;
		plug_exec_list_node(msh, exec_list_node);
	}
}