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

void	do_redir(t_msh *msh, t_redirect redir_box)
{
	if (redir_box.exp_type == R_ORIGIN_REDIRECT)
		do_read_redir(msh, redir_box.str);
	/*
	else if (redir_box.exp_type == LIMITER_HEREDOC)
	{
		clear_hd(msh);
		msh->exec->hd = new_hd();
		redir_hd_content(msh, redir_box.str);
	}
	else if (redir_box.exp_type == W_DEST_REDIRECT)
		do_write_redir(ex_lst_nde, redir_box.str);
	else if (redir_box.exp_type == WA_DEST_REDIRECT)
		do_wapp_redir(ex_lst_nde, redir_box.str);
	*/
}


void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node)
{
	int	i;

	i = -1;
	while (++i < exec_list_node->nb_redirects)
		do_redir(msh, exec_list_node->redirect_array[i]);
}

void	pipex_loop(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	//int i = 0;
	while (exec_list_node)
	{
		ft_pipe(msh);
		ft_fork(msh);
		if (!(msh->exec->child))
		{
			//printf("%d\n", i);
			//print_exec_list_node(exec_list_node);
			ft_close(msh->exec->pipefd[READ]);
			do_all_redirections(msh, exec_list_node);
		/*
			if (exec_list_node->next)
				pipe_redirect();
			
			if (!use_builtin_code(is_a_builtin(exec_list_node->cmd)))
				ft_execve(ppx);
			else
		*/
			exit(EXIT_SUCCESS);

		}
		ft_close(msh->exec->pipefd[WRITE]);
		ft_close(msh->exec->fd_temp);
		ft_duptwo(msh->exec->pipefd[READ], msh->exec->fd_temp);
		close(msh->exec->pipefd[READ]);
		//free_after_iteration(ppx); // a tester en commentant


		exec_list_node = exec_list_node->next;
		//i++;
		sleep(1);
	}
}

void	add_hd_node(t_msh *msh, char *line)
{
	t_hd	*hd_node;
	t_hd	*new;

	hd_node = msh->exec->hd;
	new = new_hd();
	if (new)
	{
		while (hd_node->next)
			hd_node = hd_node->next;
	}
	hd_node->next = new;
	new->str = ft_strdup(line);
}
/*
void	get_here_doc_content(t_ppx *ppx)
{
	char	*line;
	t_hdc	*node;

	line = NULL;
	node = NULL;
	ppx->delimiter = ft_strjoin(ppx, ppx->av[2], "\n");
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		line = get_next_line(ppx, STDIN_FILENO);
		if (ft_strcmp(line, ppx->delimiter))
			break ;
		node = (t_hdc *)malloc(sizeof(t_hdc));
		if (!node)
			exit(EXIT_FAILURE);
		node->s = ft_strdup(ppx, line);
		append_node_hdcstring(ppx, node);
		free_chars(&line);
	}
	free_chars(&line);
}
*/

t_bool hd_strcmp(char *limiter, char *line)
{
	char	*limiter_with_nl;
	t_bool	return_value;

	limiter_with_nl = ft_strjoin(limiter, "\n");
	if (ft_strcmp(limiter_with_nl, line))
		return_value = TRUE;
	else
		return_value = FALSE;
	free(limiter_with_nl);
	return (return_value);
}

void	get_hd(t_exec_list *exec_list_node, int i)
{
	char	*line;
	t_hd	*hd_node; // continuer ici

	line = NULL;
	while (42)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (hd_strcmp(exec_list_node->redirect_array[i].str, line))
			break ;
		


		else
			msh->exec->hd->str = ft_strdup(line);
		free(line);
		i++;
	}
	free(line);
}

void	clear_hd(t_exec_list *exec_list_node)
{
	t_hd	*hd_node;
	t_hd	*hd_node_next;

	hd_node = exec_list_node->hd;
	hd_node_next = NULL;
	while (hd_node)
	{
		hd_node_next = hd_node->next;
		if (hd_node->str)
		{
			free(hd_node->str);
			hd_node->str = NULL;
		}
		free(hd_node);
		hd_node = hd_node_next;
	}
}

void	get_hd_in_exec_list_node(t_exec_list *exec_list_node)
{
	int	i;

	i = -1;
	while (++i < exec_list_node->nb_redirects)
	{
		if (exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
		{
			if (exec_list_node->hd->str)
			{
				clear_hd(exec_list_node);
				exec_list_node->hd = new_hd();
			}
			get_hd(exec_list_node, i);
		}
	}
}

t_bool	hd_in_exec_list_node(t_exec_list *exec_list_node)
{
	int		i;

	i = -1;
	while (++i < exec_list_node->nb_redirects)
	{
		if (exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
			return (TRUE);
	}
	return (FALSE);
}

void	get_all_hd_content(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	while (exec_list_node)
	{
		if (hd_in_exec_list_node(exec_list_node))
		{
			exec_list_node->hd = new_hd();
			get_hd_in_exec_list_node(exec_list_node);
		}
		exec_list_node = exec_list_node->next;
	}
}

void execution(t_msh *msh, int ac, char **av, char **envp)
{
	msh->exec = new_exec();
	init_exec(msh);

	feed_msh_acavenvp(msh, ac, av, envp);

	get_all_hd_content(msh);

	//print_paths_from_path(msh);

	/*
	pipex_loop(msh);
	close(ppx->fd_temp);
	close(ppx->pipefd[READ]);
	close(ppx->pipefd[WRITE]);

	while (waitpid(-1, &(msh->return_value), 0) != -1)
		;
	*/
}
