#include "minishell.h"

static int print = 0;

void	print_exp_type_in_exec_array(t_exec_list *exec_list_node, int i)
{
	int exp_type = exec_list_node->redir_array[i].exp_type;

	if (exp_type == WORD_EXPANDED)
	{
		if (print) {dprintf(2, "(WORD_EXPANDED)");}
	}
	else if (exp_type == R_ORIGIN_REDIRECT)
	{
		if (print) {dprintf(2, "(R_ORIGIN_REDIRECT)");}
	}
	else if (exp_type == LIMITER_HEREDOC)
	{
		if (print) {dprintf(2, "(LIMITER_HEREDOC)");}
	}
	else if (exp_type == W_DEST_REDIRECT)
	{
		if (print) {dprintf(2, "(W_DEST_REDIRECT)");}
	}
	else if (exp_type == WA_DEST_REDIRECT)
	{
		if (print) {dprintf(2, "(WA_DEST_REDIRECT)");}
	}
	else if (exp_type == PIPE_EXPANDED)
	{
		if (print) {dprintf(2, "(PIPE_EXPANDED)");}
	}
	else if (exp_type == HEREDOC_ERASED)
	{
		if (print) {dprintf(2, "(HEREDOC_ERASED)");}
	}
}

void	print_redir_array(t_exec_list *exec_list_node)
{
	if (exec_list_node->redir_array)
	{
		int i = -1;

		while (++i < exec_list_node->nb_redirects)
		{
			print_exp_type_in_exec_array(exec_list_node, i);
			if (print) {dprintf(2, "exec_list_node->redir_array[%d].str = %s\n", i, exec_list_node->redir_array[i].str);}
		}
	}
	else
		if (print) {dprintf(2, "Le tableau des redirections est vide.\n");}
}

void	print_ntcharss_execln(t_exec_list *exec_list_node)
{
	int	i = -1;

	if (exec_list_node->args_array)
	{
		while (++i < exec_list_node->nb_words)
			if (print) {dprintf(2, "exec_list_node->args_array[%d] = %s\n", i, exec_list_node->args_array[i]);}
	}
}

void	print_args_array(t_exec_list *exec_list_node)
{
	if (exec_list_node->args_array)
		print_ntcharss_execln(exec_list_node);
	else
		if (print) {dprintf(2, "Le tableau des arguments est vide.\n");}
}

void	print_pos_ppl_in_exec_list_node(t_exec_list *exec_list_node)
{
	if (print) {dprintf(2, "exec_list_node->pos_ppl = ");}
	if (exec_list_node->pos_ppl == INIT_POS_PPL_VALUE)
	{
		if (print) {dprintf(2, "INIT_POS_PPL_VALUE\n");}
	}
	else if (exec_list_node->pos_ppl == FIRST)
	{
		if (print) {dprintf(2, "FIRST\n");}
	}
	else if (exec_list_node->pos_ppl == MIDDLE)
	{
		if (print) {dprintf(2, "MIDDLE\n");}
	}
	else if (exec_list_node->pos_ppl == LAST)
	{
		if (print) {dprintf(2, "LAST\n");}
	}
	else if (exec_list_node->pos_ppl == SOLO)
	{
		if (print) {dprintf(2, "SOLO\n");}
	}
}

void	print_exec_list_node(t_exec_list *exec_list_node)
{
	if (print) {dprintf(2, "exec_list_node->nb_redirects = %d\n", exec_list_node->nb_redirects);}
	if (print) {dprintf(2, "exec_list_node->nb_words = %d\n", exec_list_node->nb_words);}
	if (print) {dprintf(2, "exec_list_node->next_pipe = %d\n", exec_list_node->next_pipe);}
	if (print) {dprintf(2, "exec_list_node->nb_pipes = %d\n", exec_list_node->nb_pipes);}
	print_redir_array(exec_list_node);
	if (print) {dprintf(2, "exec_list_node->cmd = %s\n", exec_list_node->cmd);}
	print_args_array(exec_list_node);
	if (print) {dprintf(2, "exec_list_node->contains_hd = %d\n", exec_list_node->contains_hd);}
	/*
	if (exec_list_node->contains_hd)
		print_hd_in_exec_list_node(exec_list_node);
	*/
	if (print) {dprintf(2, "exec_list_node->contains_write_redirects = %d\n", exec_list_node->contains_write_redirect);}
	print_pos_ppl_in_exec_list_node(exec_list_node);
}

void	print_exec_list(t_msh *msh)
{
	t_exec_list	*exec_list = msh->exec_list;

	while (exec_list)
	{
		if (print) {dprintf(2, "\n==NEW EXEC_LIST_NODE==\n");}
		print_exec_list_node(exec_list);
		exec_list = exec_list->next;
		if (print) {dprintf(2, "==END OF NODE==\n");}
	}
}