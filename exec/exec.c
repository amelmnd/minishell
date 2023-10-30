#include "minishell.h"

// partie post fin expander


// partie pré fin expander

/*
static int	search_cmd_among_paths(t_ppx *ppx)
{
	char	*abs_path_cmd;
	int		access_value;

	if (!ppx->paths_from_path)
		nsfod_msg(ppx, ppx->num_cmd);
	abs_path_cmd = NULL;
	ppx->i = -1;
	access_value = 0;
	build_slash_and_cmd(ppx);
	while (ppx->paths_from_path[++(ppx->i)])
	{
		ppx->chars_temp = ft_strdup(ppx, ppx->paths_from_path[ppx->i]);
		abs_path_cmd = ft_strjoin(ppx, ppx->chars_temp, ppx->slash_and_cmd);
		free_chars(&(ppx->chars_temp));
		access_value = access(abs_path_cmd, X_OK);
		if (!access_value)
			break ;
		free_chars(&abs_path_cmd);
	}
	if (access_value == -1)
		cmd_not_found_msg(ppx);
	ppx->abs_path_cmd = abs_path_cmd;
	return (!access_value);
}

static char	*get_only_the_cmd(t_ppx *ppx, char *abs_path_to_cmd)
{
	char	**relics;
	int		ntcharss_size;
	char	*only_the_cmd;

	relics = ft_split(ppx, abs_path_to_cmd, '/');
	ntcharss_size = get_size_ntcharss(relics);
	only_the_cmd = ft_strdup(ppx, relics[ntcharss_size -1]);
	free_charss(&relics);
	return (only_the_cmd);
}

static int	check_valid_cmd_abs_path(char *path)
{
	int		access_value;

	access_value = access(pot_rtu_cmd_without_args, X_OK);
	if (!access_value)
	{
		ppx->abs_path_cmd = ft_strdup(ppx, pot_rtu_cmd_without_args);
		ppx->args = ntcharss_copy(ppx, pot_rtu_cmd_with_args);
		free_chars(&(ppx->args[0]));
		ppx->args[0] = get_only_the_cmd(ppx, pot_rtu_cmd_without_args);
	}
	free_chars(&pot_rtu_cmd_without_args);
	free_charss(&pot_rtu_cmd_with_args);
	if (!access_value)
		return (1);
	return (0);
}

int	cmd_parsing(t_ppx *ppx)
{
	if (!ft_strlen(ppx->av[ppx->num_cmd]))
	{
		write(2, "bash: '': command not found\n", 28);
		return (0);
	}
	if (!check_valid_cmd_abs_path(str))
		return (search_cmd_among_paths(ppx));
	else
		return (1);
	return (0);
}

int	is_a_builtin(char *exec_list_node_cmd)
{
	if (ft_strcmp(exec_list_node_cmd, "echo"))
		return (1);
	else if (ft_strcmp(exec_list_node_cmd, "cd"))
		return (2);
	else if (ft_strcmp(exec_list_node_cmd, "pwd"))
		return (3);
	else if (ft_strcmp(exec_list_node_cmd, "export"))
		return (4);
	else if (ft_strcmp(exec_list_node_cmd, "unset"))
		return (5);
	else if (ft_strcmp(exec_list_node_cmd, "env"))
		return (6);
	else if (ft_strcmp(exec_list_node_cmd, "exit"))
		return (7);
	return (0);
}

int	use_builtin_code(int num_builtin)
{
	if (!num_builtin || num_builtin > 7)
		return (0);
	if (num_builtin == 1)
		echo_builtin();
	else if (num_builtin == 2)
		cd_builtin();
	else if (num_builtin == 3)
		pwd_builtin();
	else if (num_builtin == 4)
		export_builtin();
	else if (num_builtin == 5)
		unset_builtin();
	else if (num_builtin == 6)
		env_builtin();
	else if (num_builtin == 7)
		exit_builtin();
	return (1);
}
*/


void	do_read_redir(t_msh *msh, char *origin)
{
	msh->exec->fd_read_redirect = open(origin, O_RDONLY);
	if (msh->exec->fd_read_redirect == -1)
	{
		printf("minishell : %s\n", strerror(errno)); // message à ajuster plus tard
		ft_close(msh->exec->pipefd[WRITE]);
		exit(EXIT_FAILURE); // ajuster plus tard la valeur de retour ici
		////exit à réactiver plus tard
	}
	ft_duptwo(msh->exec->fd_read_redirect, STDIN_FILENO);
	ft_close(msh->exec->fd_read_redirect); // a tester en commentant
}

void	retrieve_hd_content_through_hdpipe(t_exec_list *exec_list_node, int j)
{
	printf("retrieve_hd_content_through_hdpipe AVANT LE DUP2 ; PROCESSUS n°%d ; hd_pipe[READ] = %d\n", j, exec_list_node->hd_pipe[READ]);
	int ret = dup2(exec_list_node->hd_pipe[READ], STDIN_FILENO);
	if (ret == -1)
		perror("dup2 error");
	printf("retrieve_hd_content_through_hdpipe APRES LE DUP2 ; PROCESSUS n°%d ; hd_pipe[READ] = %d\n", j, exec_list_node->hd_pipe[READ]);

	//ft_duptwo(exec_list_node->hd_pipe[READ], STDIN_FILENO);
	close(exec_list_node->hd_pipe[WRITE]);
	close(exec_list_node->hd_pipe[READ]);
	printf("retrieve_hd_content_through_hdpipe ; PROCESSUS numéro %d : Sortie\n", j);
}

void	do_redir(t_msh *msh, t_exec_list *exec_list_node, int i, int j)
{
	t_redirect	redir_box;

	redir_box = exec_list_node->redirect_array[i];
	if (redir_box.exp_type == LIMITER_HEREDOC)
	{
		retrieve_hd_content_through_hdpipe(exec_list_node, j);
		//printf("do_redir ; execve cat imminent\n");
		//execve("/bin/cat", (char *[]){ "cat", NULL }, msh->exec->envp);
		//redir_hd_content(msh, redir_box.str);
	}
	/*
	else if (redir_box.exp_type == R_ORIGIN_REDIRECT)
		do_read_redir(msh, redir_box.str);
	else if (redir_box.exp_type == W_DEST_REDIRECT)
		do_write_redir(ex_lst_nde, redir_box.str);
	else if (redir_box.exp_type == WA_DEST_REDIRECT)
		do_wapp_redir(ex_lst_nde, redir_box.str);
	*/
}

void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node, int j)
{
	int	i;

	i = -1;
	while (++i < exec_list_node->nb_redirects)
		do_redir(msh, exec_list_node, i, j);
}

void	exec_loop(t_msh *msh)
{
	printf("exec_loop : Entrée\n");
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	int j = 0;
	while (exec_list_node)
	{
		ft_pipe(msh);
		if (exec_list_node->contains_hd)
		{
			
			printf("exec_loop(while) ; PROCESSUS n° %d (parent, après le send (donc le pipe)) ; exec_list_node->hd_pipe[READ] = %d ; exec_list_node->hd_pipe[WRITE] = %d", j, exec_list_node->hd_pipe[READ], exec_list_node->hd_pipe[WRITE]);
		}
		ft_fork(msh);
		if (!(msh->exec->child))
		{
			printf("PROCESSUS numéro %d\n", j);
			//print_exec_list_node(exec_list_node);
			
			printf("exec_loop(while) ; PROCESSUS n° %d (enfant) ; exec_list_node->hd_pipe[READ] = %d ; exec_list_node->hd_pipe[WRITE] = %d", j, exec_list_node->hd_pipe[READ], exec_list_node->hd_pipe[WRITE]);

			if (exec_list_node->contains_hd)
				close(exec_list_node->hd_pipe[WRITE]);

			//do_all_redirections(msh, exec_list_node, j);
		/*
			if (exec_list_node->next)
				pipe_redirect();
			
			if (!use_builtin_code(is_a_builtin(exec_list_node->cmd)))
				ft_execve(ppx);
			else
		*/
			exit(EXIT_SUCCESS);

		}
		else
			send_hd_through_pipe(exec_list_node, j);
		ft_close(msh->exec->fd_temp);
		ft_duptwo(msh->exec->pipefd[READ], msh->exec->fd_temp);
		close(msh->exec->pipefd[READ]);
		//free_after_iteration(ppx); // a tester en commentant


		exec_list_node = exec_list_node->next;
		j++;
		sleep(1);
	}
}

void execution(t_msh *msh, int ac, char **av, char **envp)
{
	msh->exec = new_exec();
	init_exec(msh);


	get_all_hd_content(msh);
	//print_all_hd_remaining(msh);
	//send_hd_through_pipe(msh); //déplacé dans l'exec_loop, pendant le fork
	mark_all_erased_hd(msh);
	print_exec_list(msh);

	//print_paths_from_path(msh);

	
	feed_msh_acavenvp(msh, ac, av, envp);
	exec_loop(msh);
	/*
	close(ppx->fd_temp);
	close(ppx->pipefd[READ]);
	close(ppx->pipefd[WRITE]);
	*/

	while (waitpid(-1, &(msh->return_value), 0) != -1)
		;
	
}
