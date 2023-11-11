#include "minishell.h"

void	ft_pipe(t_msh *msh)
{
	/*
	if (pipe(ppx->pipefd) == -1)
		errormsg_free_exit(ppx, "bash");
	*/
	// penser à prévoir les cas d'erreur avec le bloc ci-dessus

	pipe(msh->exec->pipefd);
}
void	ft_fork(t_msh *msh)
{
	/*
	if (ppx->child == -1)
		errormsg_free_exit(ppx, "bash");
	*/
	// penser à prévoir les cas d'erreur avec le bloc ci-dessus

	msh->exec->child = fork();
}

void	ft_close(int fd)
{
	/*
	if (fd != -1)
	{
		if (close(fd) == -1)
			errormsg_free_exit(ppx, "bash");
	}
	// vérifier la valeur du fd avant de le close
	*/
	// penser à prévoir les cas d'erreur avec le bloc ci-dessus

	close(fd);
}

void	ft_duptwo(int pretender, int to_replace)
{
	if (dup2(pretender, to_replace) == -1)
		perror("dup2 error");
}
