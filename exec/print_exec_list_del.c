#include "minishell.h"

void	print_exp_type_in_exec_array(t_exec_list *exec_list_node, int i)
{
	int exp_type = exec_list_node->redirect_array[i].exp_type;

	if (exp_type == WORD_EXPANDED)
		printf("(WORD_EXPANDED)");
	else if (exp_type == R_ORIGIN_REDIRECT)
		printf("(R_ORIGIN_REDIRECT)");
	else if (exp_type == LIMITER_HEREDOC)
		printf("(LIMITER_HEREDOC)");
	else if (exp_type == W_DEST_REDIRECT)
		printf("(W_DEST_REDIRECT)");
	else if (exp_type == WA_DEST_REDIRECT)
		printf("(WA_DEST_REDIRECT)");
	else if (exp_type == PIPE_EXPANDED)
		printf("(PIPE_EXPANDED)");
	else if (exp_type == HEREDOC_ERASED)
		printf("(HEREDOC_ERASED)");
}

void	print_redirect_array(t_exec_list *exec_list_node)
{
	if (exec_list_node->redirect_array)
	{
		int i = -1;

		while (++i < exec_list_node->nb_redirects)
		{
			print_exp_type_in_exec_array(exec_list_node, i);
			printf("exec_list_node->redirect_array[%d].str = %s\n", i, exec_list_node->redirect_array[i].str);
		}
	}
	else
		printf("Le tableau des redirections est vide.\n");
}

void	print_charss_execln(t_exec_list *exec_list_node)
{
	int	i = -1;

	if (exec_list_node->args_array)
	{
		while (++i < exec_list_node->nb_words)
			printf("exec_list_node->args_array[%d] = %s\n", i, exec_list_node->args_array[i]);
	}
}

void	print_args_array(t_exec_list *exec_list_node)
{
	if (exec_list_node->args_array)
		print_charss_execln(exec_list_node);
	else
		printf("Le tableau des arguments est vide.\n");
}

void	print_pos_ppl_in_exec_list_node(t_exec_list *exec_list_node)
{
	printf("exec_list_node->pos_ppl = ");
	if (exec_list_node->pos_ppl == INIT_POS_PPL_VALUE)
		printf("INIT_POS_PPL_VALUE\n");
	else if (exec_list_node->pos_ppl == FIRST)
		printf("FIRST\n");
	else if (exec_list_node->pos_ppl == MIDDLE)
		printf("MIDDLE\n");
	else if (exec_list_node->pos_ppl == LAST)
		printf("LAST\n");
	else if (exec_list_node->pos_ppl == SOLO)
		printf("SOLO\n");
}

void	print_exec_list_node(t_exec_list *exec_list_node)
{
	printf("exec_list_node->nb_redirects = %d\n", exec_list_node->nb_redirects);
	printf("exec_list_node->nb_words = %d\n", exec_list_node->nb_words);
	printf("exec_list_node->next_pipe = %d\n", exec_list_node->next_pipe);
	printf("exec_list_node->nb_pipes = %d\n", exec_list_node->nb_pipes);
	print_redirect_array(exec_list_node);
	printf("exec_list_node->cmd = %s\n", exec_list_node->cmd);
	print_args_array(exec_list_node);
	printf("exec_list_node->contains_hd = %d\n", exec_list_node->contains_hd);
	if (exec_list_node->contains_hd)
		print_hd_in_exec_list_node(exec_list_node);
	printf("exec_list_node->contains_write_redirects = %d\n", exec_list_node->contains_write_redirect);
	print_pos_ppl_in_exec_list_node(exec_list_node);
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