#include "minishell.h"

void	print_exp_type_in_exec_array(t_exec_list *exec_list_node, int i)
{
	int exp_type = exec_list_node->redirect_array[i].exp_type;

	if (exp_type == WORD_EXPANDED)
		dprintf(2, "(WORD_EXPANDED)");
	else if (exp_type == R_ORIGIN_REDIRECT)
		dprintf(2, "(R_ORIGIN_REDIRECT)");
	else if (exp_type == LIMITER_HEREDOC)
		dprintf(2, "(LIMITER_HEREDOC)");
	else if (exp_type == W_DEST_REDIRECT)
		dprintf(2, "(W_DEST_REDIRECT)");
	else if (exp_type == WA_DEST_REDIRECT)
		dprintf(2, "(WA_DEST_REDIRECT)");
	else if (exp_type == PIPE_EXPANDED)
		dprintf(2, "(PIPE_EXPANDED)");
	else if (exp_type == HEREDOC_ERASED)
		dprintf(2, "(HEREDOC_ERASED)");
}

void	print_redirect_array(t_exec_list *exec_list_node)
{
	if (exec_list_node->redirect_array)
	{
		int i = -1;

		while (++i < exec_list_node->nb_redirects)
		{
			print_exp_type_in_exec_array(exec_list_node, i);
			dprintf(2, "exec_list_node->redirect_array[%d].str = %s\n", i, exec_list_node->redirect_array[i].str);
		}
	}
	else
		dprintf(2, "Le tableau des redirections est vide.\n");
}

void	print_charss_execln(t_exec_list *exec_list_node)
{
	int	i = -1;

	if (exec_list_node->args_array)
	{
		while (++i < exec_list_node->nb_words)
			dprintf(2, "exec_list_node->args_array[%d] = %s\n", i, exec_list_node->args_array[i]);
	}
}

void	print_args_array(t_exec_list *exec_list_node)
{
	if (exec_list_node->args_array)
		print_charss_execln(exec_list_node);
	else
		dprintf(2, "Le tableau des arguments est vide.\n");
}

void	print_pos_ppl_in_exec_list_node(t_exec_list *exec_list_node)
{
	dprintf(2, "exec_list_node->pos_ppl = ");
	if (exec_list_node->pos_ppl == INIT_POS_PPL_VALUE)
		dprintf(2, "INIT_POS_PPL_VALUE\n");
	else if (exec_list_node->pos_ppl == FIRST)
		dprintf(2, "FIRST\n");
	else if (exec_list_node->pos_ppl == MIDDLE)
		dprintf(2, "MIDDLE\n");
	else if (exec_list_node->pos_ppl == LAST)
		dprintf(2, "LAST\n");
	else if (exec_list_node->pos_ppl == SOLO)
		dprintf(2, "SOLO\n");
}

void	print_exec_list_node(t_exec_list *exec_list_node)
{
	dprintf(2, "exec_list_node->nb_redirects = %d\n", exec_list_node->nb_redirects);
	dprintf(2, "exec_list_node->nb_words = %d\n", exec_list_node->nb_words);
	dprintf(2, "exec_list_node->next_pipe = %d\n", exec_list_node->next_pipe);
	dprintf(2, "exec_list_node->nb_pipes = %d\n", exec_list_node->nb_pipes);
	print_redirect_array(exec_list_node);
	dprintf(2, "exec_list_node->cmd = %s\n", exec_list_node->cmd);
	print_args_array(exec_list_node);
	dprintf(2, "exec_list_node->contains_hd = %d\n", exec_list_node->contains_hd);
	if (exec_list_node->contains_hd)
		print_hd_in_exec_list_node(exec_list_node);
	dprintf(2, "exec_list_node->contains_write_redirects = %d\n", exec_list_node->contains_write_redirect);
	print_pos_ppl_in_exec_list_node(exec_list_node);
}

void	print_exec_list(t_msh *msh)
{
	t_exec_list	*exec_list = msh->exec_list;

	while (exec_list)
	{
		dprintf(2, "\n==NEW EXEC_LIST_NODE==\n");
		print_exec_list_node(exec_list);
		exec_list = exec_list->next;
		dprintf(2, "==END OF NODE==\n");
	}
}