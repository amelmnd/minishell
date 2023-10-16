#include "minishell.h"

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

void	init_msh(t_msh *msh)
{
	msh->lexer_list = NULL;
	msh->exp_list = new_exp_list_node();
	msh->exec_list = NULL;
	msh->timestamp = new_timestamp();
}