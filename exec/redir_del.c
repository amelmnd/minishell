#include "minishell.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
static int print = 0;

void	do_read_redir(t_msh *msh, char *origin, int j)
{
	if (print) {dprintf(2, "do_read_redir(%d) ; Entrée\n", j);}
	if (msh && msh->exec)
	{
		msh->exec->fd_read_redirect = open(origin, O_RDONLY);
		if (msh->exec->fd_read_redirect == -1)
		{
			printf("minishell: %s: %s\n", origin, strerror(errno));
			exit(1);
		}
		else
			ft_duptwo(msh->exec->fd_read_redirect, STDIN_FILENO);
	}
	if (print) {dprintf(2, "do_read_redir(%d) ; Sortie\n", j);}
}

void	do_write_redir(t_msh *msh, char *dest, int j)
{
	if (print) {dprintf(2, "do_write_redir(%d) ; Entrée\n", j);}
	if (msh && msh->exec)
	{
		msh->exec->fd_write_redirect = open(dest,
			O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (msh->exec->fd_write_redirect == -1)
		{
			printf("minishell: %s: %s\n", dest, strerror(errno));
			exit(1);
		}
		else
			ft_duptwo(msh->exec->fd_write_redirect, STDOUT_FILENO);
	}
	if (print) {dprintf(2, "do_write_redir(%d) ; Sortie\n", j);}
}

void	do_wapp_redir(t_msh *msh, char *dest, int j)
{
	if (print) {dprintf(2, "do_wapp_redir(%d) ; Entrée\n", j);}
	if (msh && msh->exec)
	{
		msh->exec->fd_write_redirect = open(dest,
			O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (msh->exec->fd_write_redirect == -1)
		{
			printf("minishell: %s: %s\n", dest, strerror(errno));
			exit(1);
		}
		else
			ft_duptwo(msh->exec->fd_write_redirect, STDOUT_FILENO);
	}
	if (print) {dprintf(2, "do_wapp_redir(%d) ; Sortie\n", j);}
}

void	do_redir(t_msh *msh, t_exec_list *exec_list_node, int i, int j)
{
	if (print) {dprintf(2, "do_redir : Entrée\n");}
	t_redirect	redir_box;

	if (msh && exec_list_node && exec_list_node->redirect_array)
	{
		redir_box = exec_list_node->redirect_array[i];
		if (redir_box.exp_type == LIMITER_HEREDOC)
			retrieve_hd_through_hdpipe(exec_list_node, j);
		else if (redir_box.exp_type == R_ORIGIN_REDIRECT)
			do_read_redir(msh, redir_box.str, j);
		else if (redir_box.exp_type == W_DEST_REDIRECT)
			do_write_redir(msh, redir_box.str, j);
		else if (redir_box.exp_type == WA_DEST_REDIRECT)
			do_wapp_redir(msh, redir_box.str, j);
		/*
		// à activer quand l'enum AMBIGUOUS_REDIRECT sera assigné dans l'expander
		else if (redir_box.exp_type == AMBIGUOUS_REDIRECT)
		{
			printf("minishell: %s: ambiguous redirect\n", redir_box.str);
			exit(1);
		}
		*/
	}
	if (print) {dprintf(2, "do_redir : Sortie\n");}
}

void	manage_stdin(t_msh *msh, t_exec_list *exec_list_node, int j)
{
	if (print) {dprintf(2, "manage_stdin (%d): Entrée\n", j);}
	if (msh && msh->exec && exec_list_node)
	{
		if (exec_list_node->pos_ppl == MIDDLE
			|| exec_list_node->pos_ppl == LAST)
			dup2(msh->exec->fd_temp, STDIN_FILENO);
	}
	if (print) {dprintf(2, "manage_stdin (%d): Sortie\n", j);}
}

void	manage_stdout(t_msh *msh, t_exec_list *exec_list_node, int j)
{
	if (print) {dprintf(2, "manage_stdout(%d) : Entrée\n", j);}
	if (msh && msh->exec && exec_list_node)
	{
		if ((exec_list_node->pos_ppl == FIRST
			|| exec_list_node->pos_ppl == MIDDLE)
			&& exec_list_node->contains_write_redirect == FALSE)
			dup2(msh->exec->pipefd[WRITE], STDOUT_FILENO);
	}
	if (print) {dprintf(2, "manage_stdout(%d) : Sortie\n", j);}
}

void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node, int j)
{
	if (print) {dprintf(2, "do_all_redirections : Entrée\n");}
	int	i;

	if (print) {dprintf(2, "do_all_redirections(%d) : état des fd AVANT tous les redir et close\n", j);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->pipefd[READ] = %d\n", j, msh->exec->pipefd[READ]);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->pipefd[WRITE] = %d\n", j, msh->exec->pipefd[WRITE]);}
	if (print) {dprintf(2, "do_all_redirections(%d) : STDIN_FILENO = %d\n", j, STDIN_FILENO);}
	if (print) {dprintf(2, "do_all_redirections(%d) : STDOUT_FILENO = %d\n", j, STDOUT_FILENO);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->fd_temp = %d\n", j, msh->exec->fd_temp);}
	if (print) {dprintf(2, "do_all_redirections(%d) : exec_list_node->hd_pipe[READ] = %d\n", j, exec_list_node->hd_pipe[READ]);}
	if (print) {dprintf(2, "do_all_redirections(%d) : exec_list_node->hd_pipe[WRITE] = %d\n", j, exec_list_node->hd_pipe[WRITE]);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->fd_write_redirect = %d\n", j, msh->exec->fd_write_redirect);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->fd_read_redirect = %d\n", j, msh->exec->fd_read_redirect);}

	if (msh && msh->exec && exec_list_node)
	{
		if (exec_list_node->pos_ppl != SOLO || exec_list_node->pos_ppl != FIRST)
			close(msh->exec->pipefd[READ]);
		manage_stdin(msh, exec_list_node, j);
		if (exec_list_node->contains_hd)
			close(exec_list_node->hd_pipe[WRITE]);
		i = -1;
		while (++i < exec_list_node->nb_redirects)
			do_redir(msh, exec_list_node, i, j);
		manage_stdout(msh, exec_list_node, j);
		if (exec_list_node->pos_ppl == MIDDLE || exec_list_node->pos_ppl == LAST)
		{
			close(msh->exec->fd_temp);
			close(msh->exec->pipefd[WRITE]);
		}
		if (exec_list_node->contains_read_redirect)
			close(msh->exec->fd_read_redirect);
		if (exec_list_node->contains_write_redirect)
			close(msh->exec->fd_write_redirect);
	}

	if (print) {dprintf(2, "do_all_redirections(%d) : état des fd APRES tous les redir et close\n", j);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->pipefd[READ] = %d\n", j, msh->exec->pipefd[READ]);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->pipefd[WRITE] = %d\n", j, msh->exec->pipefd[WRITE]);}
	if (print) {dprintf(2, "do_all_redirections(%d) : STDIN_FILENO = %d\n", j, STDIN_FILENO);}
	if (print) {dprintf(2, "do_all_redirections(%d) : STDOUT_FILENO = %d\n", j, STDOUT_FILENO);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->fd_temp = %d\n", j, msh->exec->fd_temp);}
	if (print) {dprintf(2, "do_all_redirections(%d) : exec_list_node->hd_pipe[READ] = %d\n", j, exec_list_node->hd_pipe[READ]);}
	if (print) {dprintf(2, "do_all_redirections(%d) : exec_list_node->hd_pipe[WRITE] = %d\n", j, exec_list_node->hd_pipe[WRITE]);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->fd_write_redirect = %d\n", j, msh->exec->fd_write_redirect);}
	if (print) {dprintf(2, "do_all_redirections(%d) : msh->exec->fd_read_redirect = %d\n", j, msh->exec->fd_read_redirect);}

	if (print) {dprintf(2, "do_all_redirections : Sortie\n");}
}
