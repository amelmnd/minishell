#include "minishell.h"

/*
void	fill_the_first_node(t_msh *msh)
{
	t_exp_list *first_node = NULL;

	if (msh)
	{
		if (msh->exp_list)
		{
			while (msh->exp_list->previous)
			{
				print_node(first_node);
				first_node = msh->exp_list->previous;
			}
		}
	}
	if (!first_node)
		first_node = msh->exp_list;
	first_node->str = gen_random_str(msh);
}


t_exp_list	*new_exp_list_node(void)
{
	t_exp_list *new_node;

	new_node = NULL;
	new_node = (t_exp_list *)malloc(sizeof(t_exp_list));
	if (!new_node)
		return (NULL);
	return (new_node);
}

void	init_node_exp_list(t_msh *msh)
{
	msh->exp_list->previous = NULL;
	msh->exp_list->next = NULL;
	msh->exp_list->str = NULL;
	msh->exp_list->exp_type = 0;
}

void	add_exp_list_node(t_msh *msh, t_exp_list *node)
{
	t_exp_list	*node_i;

	node_i = msh->exp_list;
	while (node_i->next)
		node_i = node_i->next;
	node_i->next = node;
	node->previous = node_i;
}

void	feed_exp_list_node(t_exp_list *exp_list, char *str, int exp_type)
{
	exp_list->str = str;
	exp_list->exp_type = exp_type;
}

void	add_pipe_exp_list_node(t_msh *msh)
{
	t_exp_list	*pipe_exp_list_node;

	pipe_exp_list_node = new_exp_list_node();
	feed_exp_list_node(pipe_exp_list_node, NULL, 5);
	add_exp_list_node(msh, pipe_exp_list_node);
}
*/
