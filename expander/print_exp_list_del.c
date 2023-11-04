#include "../include/minishell.h"

void	print_exp_type(int exp_type)
{
	printf("exp_type = ");
	if (exp_type == 0)
		printf("WORD_EXPANDED\n");
	else if (exp_type == 1)
		printf("R_ORIGIN_REDIRECT\n");
	else if (exp_type == 2)
		printf("LIMITER_HEREDOC\n");
	else if (exp_type == 3)
		printf("W_DEST_REDIRECT\n");
	else if (exp_type == 4)
		printf("WA_DEST_REDIRECT\n");
	else if (exp_type == 5)
		printf("PIPE_EXPANDED\n\n");
}

void	print_node(t_exp_list *node)
{
	if (node)
	{
		printf("\n== node ==\n");
		print_exp_type(node->exp_type);
		printf("node->str = %s\n", node->str);
		printf("====\n");
	}
}
/*
void	print_exp_list(t_msh *msh)
{
	printf("===== print_explist : Entrée =====\n");
	t_exp_list *node = msh->exp_list;
	while (node)
	{
		print_node(node);
		node = node->next;
	}
	printf("===== print_explist : Sortie =====\n");
}
*/

/*
WORD_EXPANDED,
	R_ORIGIN_REDIRECT,
	LIMITER_HEREDOC,
	W_DEST_REDIRECT,
	WA_DEST_REDIRECT,
	PIPE_EXPANDED,
	HEREDOC_ERASED
*/
void	print_exp_type_one_line(int exp_type)
{
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
		printf("\n( | )\n");
	else if (exp_type == HEREDOC_ERASED)
		printf("(HEREDOC_ERASED)");
}

void	print_node_one_line(t_exp_list *exp_list_node)
{
	print_exp_type_one_line(exp_list_node->exp_type);
	if (exp_list_node->str)
		printf("%s ", exp_list_node->str);
}

void	print_exp_list_one_line(t_msh *msh)
{
	t_exp_list *node = msh->exp_list;
	while (node)
	{
		print_node_one_line(node);
		node = node->next;
	}
	printf("\n");
}
