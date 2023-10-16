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
}

void	print_node(t_exp_list *node)
{
	print_exp_type(node->exp_type);
	printf("node->str = %s\n", node->str);
}

void	print_exp_list(t_msh *msh)
{
	printf("===== print_explist : Entrée =====\n");
	t_exp_list *node = msh->exp_list;
	//nécessité de remonter au premier node ?
	while (node)
	{
		print_node(node);
		node = node->next;
	}
	printf("===== print_explist : Sortie =====\n");
}