#include "../include/minishell.h"
#include "../include/fn_dev.h"

t_msh *new_msh(void)
{
	t_msh	*new;

	new = NULL;
	new = (t_msh *)malloc(sizeof(t_msh));
	if (!new)
		return (NULL);
	return (new);
}

t_timestamp	*new_timestamp(void)
{
	t_timestamp	*new;

	new = NULL;
	new = (t_timestamp *)malloc(sizeof(t_timestamp));
	if (!new)
		return (NULL);
	return (new);
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

void	init_msh(t_msh *msh)
{
	msh->lexer_list = NULL;
	msh->exp_list = new_exp_list_node();
	msh->exec_list = NULL;
	msh->timestamp = new_timestamp();
}

int	msh_random_0_99(t_msh *msh)
{
	int	usec;

	usec = 0;
	gettimeofday(msh->timestamp, NULL);
	usec = msh->timestamp->tv_usec;
	usec %= 100;
	return (usec);
}

int	msh_random_0_127(t_msh *msh)
{
	int	usec;

	usec = 0;
	gettimeofday(msh->timestamp, NULL);
	usec = msh->timestamp->tv_usec;
	usec %= 256;
	return (usec);
}

void	add_node(t_msh *msh, t_exp_list *node)
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

void	exp_list_generator(t_msh *msh)
{
	int nb_pipe = 0;
	int i = -1;
	int nb_elt;
	int j;
	t_exp_list	*node = NULL;
	char *str = NULL;
	int exp_type = 0;

	while (nb_pipe <= 2 || nb_pipe >= 7)
		nb_pipe = msh_random_0_99(msh)%8;
	while (++i < nb_pipe + 1)
	{
		nb_elt = 0;
		while (nb_elt <= 5 || nb_elt >= 10)
			nb_elt = msh_random_0_99(msh)%10;
		j = -1;
		while (++j < nb_elt)
		{
			node = new_exp_list_node();
			str = gen_random_str(msh);
			exp_type = msh_random_0_99(msh) % 5;
			feed_exp_list_node(node, str, exp_type);
			add_exp_list_node(msh, node);
		}
		if (i != nb_pipe)
			add_pipe_exp_list_node(msh);
	}
}

void	free_msh(t_msh *msh)
{
	if (msh->lexer_list)
	{
		free(msh->lexer_list);
		msh->lexer_list = NULL;
	}
	if (msh->exp_list)
	{
		free(msh->exp_list);
		msh->exp_list = NULL;
	}
	if (msh->exec_list)
	{
		free(msh->exec_list);
		msh->exec_list = NULL;
	}
	if (msh->timestamp)
	{
		free(msh->timestamp);
		msh->timestamp = NULL;
	}
}

int	main(void)
{
	t_msh	*msh;
	
	msh = new_msh();
	init_msh(msh);
	init_node_exp_list(msh);
	exp_list_generator(msh);
	print_exp_list(msh);
	free_msh(msh);
	return (0);
}