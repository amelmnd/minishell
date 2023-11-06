#include "minishell.h"

static int print = 0;

t_redirect	*malloc_redirects_array(int size)
{
	t_redirect	*array;

	array = NULL;
	if (size)
	{
		array = (t_redirect *)malloc(sizeof(t_redirect) * size);
		if (!array)
			return (NULL);
	}
	return (array);
}

char	**malloc_charss(int size)
{
	char	**array;
	int		i;

	array = NULL;
	i = -1;
	if (size)
	{
		array = (char **)malloc(sizeof(char *) * (size + 1));
		if (!array)
			return (NULL);
	}
	while (++i < size)
		array[i] = NULL;
	array[size] = NULL;
	return (array);
}

void	malloc_exec_list_node_arrays(t_msh *msh)
{
	t_exec_list	*node;

	node = msh->exec_list;
	while (node)
	{
		if (node->nb_redirects)
			node->redirect_array = malloc_redirects_array(node->nb_redirects);
		if (node->nb_words)
			node->args_array = malloc_charss(node->nb_words);
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
			exec_list_node = exec_list_node->next;
		else if (exp_list_node->exp_type == WORD_EXPANDED)
		{
			exec_list_node->cmd = ft_strdup(exp_list_node->str);
			//exec_list_node->args_array[0] = ft_strdup(exp_list_node->str);
			exec_list_node = exec_list_node->next;
			while (exp_list_node && exp_list_node->exp_type != PIPE_EXPANDED)
				exp_list_node = exp_list_node->next;
		}
		if (exp_list_node)
			exp_list_node = exp_list_node->next;
	}
}

void	feed_the_only_exec_list_node_cmd(t_msh *msh)
{
	if (print) {dprintf(2, "feed_the_only_exec_list_node_cmd : Entrée\n");}
	t_exp_list	*exp_list_node;

	exp_list_node = msh->exp_list;
	while (exp_list_node)
	{
		if (print) {dprintf(2, "feed_the_only_exec_list_node_cmd(while) : début itération\n");}
		if (exp_list_node->exp_type == WORD_EXPANDED)
		{
			if (print) {dprintf(2, "feed_the_only_exec_list_node_cmd(while) : msh->exec_list->cmd avant le strdup = %s\n", msh->exec_list->cmd);}
			if (print) {dprintf(2, "feed_the_only_exec_list_node_cmd(while) : exp_list_node->str = %s\n", exp_list_node->str);}
			
			msh->exec_list->cmd = ft_strdup(exp_list_node->str);
			break ;
		}
		exp_list_node = exp_list_node->next;
	}
	if (print) {dprintf(2, "feed_the_only_exec_list_node_cmd : Sortie\n");}
}

void	add_a(int *arg_i, char *arg, t_exec_list *ex)
{
	ex->args_array[*arg_i] = ft_strdup(arg);
	(*arg_i)++;
}

void	add_r(int *red, t_exp_list *exp, t_exec_list *ex)
{
	ex->redirect_array[*red].exp_type = exp->exp_type;
	ex->redirect_array[*red].str = ft_strdup(exp->str);
	(*red)++;
}

void	feed_exec_list_node(t_msh *msh)
{
	if (print) {dprintf(2, "feed_exec_list_node : Entrée\n");}
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
		if (print) {dprintf(2, "feed_exec_list_node : Nouvelle itération\n");}
		if (exp_list_node->exp_type == WORD_EXPANDED)
			add_a(&args_i, exp_list_node->str, exec_list_node);
		else if (exp_list_node->exp_type != PIPE_EXPANDED)
			add_r(&redirect_i, exp_list_node, exec_list_node);
		else if (exp_list_node->exp_type == PIPE_EXPANDED)
		{
			exec_list_node = exec_list_node->next;
			reset_counts(&args_i, &redirect_i);
		}
		exp_list_node = exp_list_node->next;
	}
	if (print) {dprintf(2, "feed_exec_list_node : Sortie\n");}
}

void	set_pos_ppl(t_exec_list *exec_list_node, int i)
{
	if (!i)
		exec_list_node->pos_ppl = FIRST;
	else if (i == exec_list_node->nb_pipes)
		exec_list_node->pos_ppl = LAST;
	else
		exec_list_node->pos_ppl = MIDDLE;
}

void	assign_pos_ppl_exec_list(t_msh *msh)
{
	t_exec_list	*exec_list_node;
	int			i;

	exec_list_node = msh->exec_list;
	if (!(exec_list_node->nb_pipes))
	{
		exec_list_node->pos_ppl = SOLO;
		return ;
	}
	i = 0;
	while (exec_list_node)
	{
		set_pos_ppl(exec_list_node, i);
		i++;
		exec_list_node = exec_list_node->next;
	}
}

void	check_redir_in_exec_list_node(t_exec_list *exec_list_node)
{
	if (print) {dprintf(2, "check_wredir_in_exec_list_node : Entrée\n");}
	int	i;

	i = -1;
	while (++i < exec_list_node->nb_redirects)
	{
		if (print) {dprintf(2, "check_wredir_in_exec_list_node(while) : nouvelle itération\n");}

		if (print) {dprintf(2, "check_wredir_in_exec_list_node : exec_list_node->redirect_array[%d].exp_type = %d\n", i, exec_list_node->redirect_array[i].exp_type);}

		if (exec_list_node->redirect_array[i].exp_type == W_DEST_REDIRECT)
			if (print) {dprintf(2, "check_wredir_in_exec_list_node ; exec_list_node->redirect_array[%d].exp_type == W_DEST_REDIRECT\n", i);}
		
		if (exec_list_node->redirect_array[i].exp_type == W_DEST_REDIRECT
			|| exec_list_node->redirect_array[i].exp_type == WA_DEST_REDIRECT)
		{
			if (print) {dprintf(2, "check_wredir_in_exec_list_node(while) : entrée dans le if\n");}
			exec_list_node->contains_write_redirect = TRUE;
		}
		if (exec_list_node->redirect_array[i].exp_type == R_ORIGIN_REDIRECT
			|| exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
		{
			if (print) {dprintf(2, "check_wredir_in_exec_list_node(while) : entrée dans le if\n");}
			exec_list_node->contains_read_redirect = TRUE;
		}
	}
	if (print) {dprintf(2, "check_wredir_in_exec_list_node : Sortie\n");}
}

void	scan_write_redirect(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	while (exec_list_node)
	{
		check_redir_in_exec_list_node(exec_list_node);
		exec_list_node = exec_list_node->next;
	}
}

void	build_exec_list(t_msh *msh)
{
	msh->exec_list = new_exec_list_node();
	init_exec_list_node(msh->exec_list);
	get_nb_pipes_in_exp_list(msh);
	if (print) {dprintf(2, "build_exec_list : msh->exec_list->nb_pipes = %d\n", msh->exec_list->nb_pipes);}
	if (msh->exec_list->nb_pipes)
	{
		if (print) {dprintf(2, "build_exec_list : entrée dans le premier if\n");}
		create_and_plug_all_empty_exec_list_nodes(msh);
		feed_exec_list_node_data(msh);
		feed_last_exec_list_node_data(msh);
	}
	else
		feed_the_only_exec_list_node_data(msh);
	malloc_exec_list_node_arrays(msh);
	if (msh->exec_list->nb_pipes)
	{
		if (print) {dprintf(2, "build_exec_list : deuxième if\n");}
		feed_exec_list_node_cmd(msh);
	}
	else
	{
		if (print) {dprintf(2, "build_exec_list : deuxième else\n");}
		feed_the_only_exec_list_node_cmd(msh);
	}
		
	if (print) {dprintf(2, "build_exec_list : PROBE\n");}
	assign_pos_ppl_exec_list(msh);
	feed_exec_list_node(msh);
	scan_write_redirect(msh);
}
