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

t_hd	*new_hd(void)
{
	t_hd	*new;

	new = NULL;
	new = (t_hd *)malloc(sizeof(t_hd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->str = NULL;
	return (new);
}

void	init_exec(t_msh *msh)
{
	msh->exec->ac = 0;
	msh->exec->av= NULL;
	msh->exec->envp = NULL;
	msh->exec->path_defined = 1;
	msh->exec->path_from_envp = NULL;
	msh->exec->paths_from_path = NULL;
	msh->exec->pipefd[0] = 0;
	msh->exec->pipefd[1] = 0;
	msh->exec->fd_temp = -1;
	msh->exec->fd_read_redirect = -1;
	msh->exec->fd_write_redirect = -1;
}

void	init_msh(t_msh *msh)
{
	msh->lexer_list = NULL;
	msh->exp_list = new_exp_list_node();
	msh->exec_list = NULL;
	msh->timestamp = new_timestamp();
	msh->exec = NULL;
	msh->return_value = 0;
}