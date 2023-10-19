#include "minishell.h"

void	print_exec_list_node(t_exec_list *exec_list_node)
{
	//exec_list_node->redirect_array = NULL;
	printf("exec_list_node->nb_redirects = %d\n", exec_list_node->nb_redirects);
	//exec_list_node->cmd = NULL;
	//exec_list_node->args_array = NULL;
	printf("exec_list_node->nb_args = %d\n", exec_list_node->nb_args);
	printf("exec_list_node->next_pipe = %d\n", exec_list_node->next_pipe);
	printf("exec_list_node->nb_pipes = %d\n", exec_list_node->nb_pipes);
}

void	print_exec_list(t_msh *msh)
{
	t_exec_list	*exec_list = msh->exec_list;

	while (exec_list)
	{
		printf("\n==NEW EXEC_LIST_NODE==\n");
		print_exec_list_node(exec_list);
		exec_list = exec_list->next;
		printf("==END OF NODE==\n");
	}
}

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
	exec_list_node->nb_args = 0;
	exec_list_node->next_pipe = 0;
	exec_list_node->nb_pipes = 0;
}

void	get_nb_pipes_in_exp_list(t_msh *msh)
{
	int	nb_pipes = 0;
	t_exp_list	*exp_list_node = msh->exp_list;

	while (exp_list_node)
	{
		if (exp_list_node->exp_type == PIPE_EXPANDED)
			nb_pipes++;
		exp_list_node = exp_list_node->next;
	}
	msh->exec_list->nb_pipes = nb_pipes;
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

/*
je parcours l'exp_list:
	jusqu'à trouver un pipe :
		compter le nombre de redirections, et de non_redirections
	noter la position du pipe rencontré
*/

void	reset_counts(int *nb_w, int *nb_r)
{
	*nb_w = 0;
	*nb_r = 0;
}

void	feed_exec_list_node_data(t_msh *msh)
{
	t_exp_list	*exp_list_node;
	t_exec_list	*exec_list_node;
	int			nb_w;
	int			nb_r;

	exp_list_node = msh->exp_list;
	exec_list_node = msh->exec_list;
	nb_w = 0;
	nb_r = 0;
	while (exp_list_node)
	{
		if (exp_list_node->exp_type == WORD_EXPANDED)
			nb_w++;
		else if (exp_list_node->exp_type != PIPE_EXPANDED)
			nb_r++;
		else
		{
			exec_list_node->nb_args = nb_w;
			exec_list_node->nb_redirects = nb_r;
			exec_list_node = exec_list_node->next;
			reset_counts(&nb_w, &nb_r);
		}
		exp_list_node = exp_list_node->next;
	}
}

void	feed_last_exec_list_node_data(t_msh *msh)
{
	t_exec_list	*last_exec_list_node;
	t_exp_list	*last_pipe_exp_list_node;

	last_exec_list_node = msh->exec_list;
	last_pipe_exp_list_node = msh->exp_list;
	while (last_exec_list_node->next)
		last_exec_list_node = last_exec_list_node->next;
	while (last_pipe_exp_list_node->next)
		last_pipe_exp_list_node = last_pipe_exp_list_node->next;
	
	while (last_pipe_exp_list_node->exp_type != PIPE_EXPANDED)
	{
		if (last_pipe_exp_list_node->exp_type == WORD_EXPANDED)
			last_exec_list_node->nb_args++;
		else
			last_exec_list_node->nb_redirects++;
		last_pipe_exp_list_node = last_pipe_exp_list_node->previous;
	}
}

void	feed_the_only_exec_list_node_data(t_msh *msh)
{
	t_exp_list	*exp_list_node_i;

	exp_list_node_i = msh->exp_list;
	while (exp_list_node_i)
	{
		if (exp_list_node_i->exp_type == WORD_EXPANDED)
			msh->exec_list->nb_args++;
		else
			msh->exec_list->nb_redirects++;
		exp_list_node_i->next;
	}
}

void	malloc_redirects_array(int size)
{
	t_redirect	*array;

	array = NULL;
	array = (t_redirect *)malloc(sizeof(t_redirect) * size);
	if (!array)
		return (NULL);
	return (array);
}

void	malloc_charss(int size)
{
	char **array;

	array = NULL;
	array = (char **)malloc(sizeof(char *) * size);
	if (!array)
		return (NULL);
	return (array);
}

void	malloc_exec_list_node_arrays(t_msh *msh)
{
	t_exec_list	*node;

	node = msh->exec_list;
	while (node)
	{
		node->redirect_array = malloc_redirects_array(node->nb_redirects);
		node->args_array = malloc_charss(node->nb_args - 1);
		node = node->next;
	}
}

void	feed_exec_list_node_cmd(t_msh *msh)
{
	t_exp_list	*exp_list_node;
	t_exec_list	*exec_list_node;

	exp_list_node = msh->exp_list;
	exec_list_node = msh->exec_list;
	while (exp_list_node)
	{
		if (exp_list_node->exp_type == PIPE_EXPANDED)
			exec_list_node->next;
		if (exp_list_node->exp_type == WORD_EXPANDED)
			exec_list_node->cmd = ft_strdup(exp_list_node->str);
		exp_list_node = exp_list_node->next;
	}
}

void	feed_the_only_exec_list_node_cmd(t_msh *msh)
{

}

void	feed_exec_list_node(t_msh *msh)
{
	
	t_exp_list	*exp_list_node;
	t_exec_list	*exec_list_node;
	int			redirect_i;
	int			args_i;

	exp_list_node = msh->exp_list;
	exec_list_node = msh->exec_list;
	redirect_i = 0;
	args_i = 0;
	while (exp_list_node)
	{
		if (exp_list_node->exp_type == WORD_EXPANDED)
			args_i++;
			if (args_i == 1)

		else if (exp_list_node->exp_type != PIPE_EXPANDED)
			nb_r++;
		else
		{
			exec_list_node = exec_list_node->next;
		}
		exp_list_node = exp_list_node->next;
	}
}

void	build_exec_list(t_msh *msh)
{
	msh->exec_list = new_exec_list_node();
	init_exec_list_node(msh->exec_list);

	get_nb_pipes_in_exp_list(msh);
	if (msh->exec_list->nb_pipes)
	{
		create_and_plug_all_empty_exec_list_nodes(msh);
		feed_exec_list_node_data(msh);
		feed_last_exec_list_node_data(msh);
	}
	else
		feed_the_only_exec_list_node_data(msh);

	// pas encore testé
	malloc_exec_list_node_arrays(msh);

	if (msh->exec_list->nb_pipes)
		feed_exec_list_node_cmd(msh);
	else
		feed_the_only_exec_list_node_cmd(msh);

	feed_exec_list_node(msh);
}
