#include "minishell.h"

void	do_read_redir(t_msh *msh, char *origin)
{
	msh->exec->fd_read_redirect = open(origin, O_RDONLY);
	if (msh->exec->fd_read_redirect == -1)
		printf("minishell : %s\n", strerror(errno)); // message à ajuster plus tard
	else
		ft_duptwo(msh->exec->fd_read_redirect, STDIN_FILENO);
}

void	do_write_redir(t_msh *msh, char *dest)
{
	msh->exec->fd_write_redirect = open(dest, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (msh->exec->fd_write_redirect == -1)
		printf("minishell : %s\n", strerror(errno)); // message à ajuster plus tard
	else
		ft_duptwo(msh->exec->fd_write_redirect, STDIN_FILENO);
}

void	do_wapp_redir(t_msh *msh, char *dest)
{
	msh->exec->fd_write_redirect = open(dest, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

	if (msh->exec->fd_write_redirect == -1)
		printf("minishell : %s\n", strerror(errno)); // message à ajuster plus tard
	else
		ft_duptwo(msh->exec->fd_write_redirect, STDIN_FILENO);
}

void	do_redir(t_msh *msh, t_exec_list *exec_list_node, int i, int j)
{
	printf("do_redir : Entrée\n");
	t_redirect	redir_box;

	redir_box = exec_list_node->redirect_array[i];
	if (redir_box.exp_type == LIMITER_HEREDOC)
		retrieve_hd_through_hdpipe(exec_list_node, j);
	else if (redir_box.exp_type == R_ORIGIN_REDIRECT)
		do_read_redir(msh, redir_box.str);
	else if (redir_box.exp_type == W_DEST_REDIRECT)
		do_write_redir(msh, redir_box.str);
	else if (redir_box.exp_type == WA_DEST_REDIRECT)
		do_wapp_redir(msh, redir_box.str);
	printf("do_redir : Sortie\n");
}

void	manage_stdin(t_msh *msh, t_exec_list *exec_list_node)
{
	if (exec_list_node->pos_ppl == MIDDLE
		|| exec_list_node->pos_ppl == LAST)
		dup2(msh->exec->fd_temp, STDIN_FILENO);
}

void	manage_stdout(t_msh *msh, t_exec_list *exec_list_node)
{
	if ((exec_list_node->pos_ppl == FIRST
		|| exec_list_node->pos_ppl == MIDDLE)
		&& exec_list_node->contains_write_redirect == FALSE)
		dup2(msh->exec->pipefd[WRITE], STDOUT_FILENO);
}

void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node, int j)
{
	printf("do_all_redirections : Entrée\n");
	int	i;

	close(msh->exec->pipefd[READ]);
	manage_stdin(msh, exec_list_node);
	if (exec_list_node->contains_hd)
		close(exec_list_node->hd_pipe[WRITE]);
	i = -1;
	while (++i < exec_list_node->nb_redirects)
		do_redir(msh, exec_list_node, i, j);
	manage_stdout(msh, exec_list_node);
	close(msh->exec->fd_temp);
	close(msh->exec->fd_read_redirect);
	close(msh->exec->fd_write_redirect);
	close(msh->exec->pipefd[WRITE]);

	printf("do_all_redirections : Sortie\n");
}