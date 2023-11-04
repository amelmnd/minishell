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
	msh->exec->cmd_path_ready = NULL;
}

void	init_msh(t_msh *msh)
{
	msh->lexer_list = NULL;
	msh->exp_list = NULL;
	msh->exec_list = NULL;
	msh->exec = NULL;
}
/*
*/