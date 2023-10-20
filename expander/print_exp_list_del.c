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

void	print_exp_type_one_line(int exp_type)
{
	if (exp_type == 5)
		printf("\n");
	printf("(");
	if (exp_type == 0)
		printf("WORD");
	else if (exp_type == 1)
		printf("READ");
	else if (exp_type == 2)
		printf("LHD");
	else if (exp_type == 3)
		printf("WRITE");
	else if (exp_type == 4)
		printf("WAPP");
	else if (exp_type == 5)
		printf(" | ");
	printf(")");
	if (exp_type == 5)
		printf("\n");

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
