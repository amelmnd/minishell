#include "minishell.h"


void	do_read_redir(t_msh *msh, char *origin)
{
	msh->exec->fd_read_redirect = open(origin, O_RDONLY);
	if (msh->exec->fd_read_redirect == -1)
		printf("minishell : %s\n", strerror(errno)); // message à ajuster plus tard
	else
		ft_duptwo(msh->exec->fd_read_redirect, STDIN_FILENO);
}

void	retrieve_hd_through_hdpipe(t_exec_list *exec_list_node, int j)
{
	printf("retrieve_hd_through_hdpipe ; PROCESSUS n°%d ; hd_pipe[READ] = %d\n", j, exec_list_node->hd_pipe[READ]);
	printf("retrieve_hd_through_hdpipe ; PROCESSUS n°%d ; hd_pipe[WRITE] = %d\n", j, exec_list_node->hd_pipe[WRITE]);
	close(exec_list_node->hd_pipe[WRITE]);
	printf("retrieve_hd_through_hdpipe AVANT LE DUP2 ; PROCESSUS n°%d ; hd_pipe[READ] = %d\n", j, exec_list_node->hd_pipe[READ]);
	int ret = dup2(exec_list_node->hd_pipe[READ], STDIN_FILENO);
	if (ret == -1)
		perror("dup2 error");
	printf("retrieve_hd_through_hdpipe APRES LE DUP2 ; PROCESSUS n°%d ; hd_pipe[READ] = %d\n", j, exec_list_node->hd_pipe[READ]);
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
	{
		retrieve_hd_through_hdpipe(exec_list_node, j);
		/*
		printf("do_redir ; execve cat imminent\n");
		execve("/bin/cat", (char *[]){ "cat", NULL }, msh->exec->envp);
		*/
	}
	else if (redir_box.exp_type == R_ORIGIN_REDIRECT)
		do_read_redir(msh, redir_box.str);
	else if (redir_box.exp_type == W_DEST_REDIRECT)
		do_write_redir(msh, redir_box.str);
	else if (redir_box.exp_type == WA_DEST_REDIRECT)
		do_wapp_redir(msh, redir_box.str);
	printf("do_redir : Sortie\n");
}

void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node, int j)
{
	printf("do_all_redirections : Entrée\n");
	int	i;

	i = -1;
	if (exec_list_node->contains_hd)
		close(exec_list_node->hd_pipe[WRITE]);
	while (++i < exec_list_node->nb_redirects)
		do_redir(msh, exec_list_node, i, j);
	printf("do_all_redirections : Sortie\n");
}