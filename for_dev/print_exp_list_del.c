#include "../include/minishell.h"

void	print_exp_type(int exp_type)
{
	dprintf(2, "exp_type = ");
	if (exp_type == 0)
		dprintf(2, "WORD_EXPANDED\n");
	else if (exp_type == 1)
		dprintf(2, "R_ORIGIN_REDIRECT\n");
	else if (exp_type == 2)
		dprintf(2, "LIMITER_HEREDOC\n");
	else if (exp_type == 3)
		dprintf(2, "W_DEST_REDIRECT\n");
	else if (exp_type == 4)
		dprintf(2, "WA_DEST_REDIRECT\n");
	else if (exp_type == 5)
		dprintf(2, "PIPE_EXPANDED\n\n");
}

void	print_node(t_exp_list *node)
{
	if (node)
	{
		dprintf(2, "\n== node ==\n");
		print_exp_type(node->exp_type);
		dprintf(2, "node->str = %s\n", node->str);
		dprintf(2, "====\n");
	}
}
/*
void	print_exp_list(t_msh *msh)
{
	dprintf(2, "===== print_explist : Entrée =====\n");
	t_exp_list *node = msh->exp_list;
	while (node)
	{
		print_node(node);
		node = node->next;
	}
	dprintf(2, "===== print_explist : Sortie =====\n");
}

void	print_exp_type_one_line(int exp_type)
{
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
		dprintf(2, "\n( | )\n");
	else if (exp_type == HEREDOC_ERASED)
		dprintf(2, "(HEREDOC_ERASED)");
}

void	print_node_one_line(t_exp_list *exp_list_node)
{
	print_exp_type_one_line(exp_list_node->exp_type);
	if (exp_list_node->str)
		dprintf(2, "%s ", exp_list_node->str);
}

void	print_exp_list_one_line(t_msh *msh)
{
	t_exp_list *node = msh->exp_list;
	while (node)
	{
		print_node_one_line(node);
		node = node->next;
	}
	dprintf(2, "\n");
}
