#include "minishell.h"

// partie post fin expander


// partie pré fin expander

int	search_cmd_among_paths(t_ppx *ppx)
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

char	*get_only_the_cmd(t_ppx *ppx, char *abs_path_to_cmd)
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

int	cmd_parsing(t_msh *msh, t_exec_list *exec_list_node)
{
	if (!ft_strlen(exec_list_node->cmd))
	{
		write(2, "bash: '': command not found\n", 28);
		return (0);
	}
	if (!check_valid_cmd_abs_path(msh, exec_list_node->cmd))
		return (search_cmd_among_paths(msh, exec_list_node->cmd));
	else
		return (1);
	return (0);
}

void	exec_loop(t_msh *msh)
{
	printf("exec_loop : Entrée\n");
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	int j = 0;
	while (exec_list_node)
	{
		pipe(msh->exec->pipefd);
		ft_fork(msh);
		if (!(msh->exec->child))
		{
			printf("PROCESSUS numéro %d\n", j);
			do_all_redirections(msh, exec_list_node, j);

			//close_all_fd();

			builtin_way(msh, exec_list_node);
			
			if (cmd_parsing(msh, exec_list_node))
				ft_execve(msh, exec_list_node);

			exit(EXIT_FAILURE);
		}
		send_hd_through_pipe(exec_list_node, j);

		close(msh->exec->pipefd[WRITE]);
		close(msh->exec->fd_temp);
		dup2(msh->exec->pipefd[READ], msh->exec->fd_temp);
		close(msh->exec->pipefd[READ]);

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
	mark_all_erased_hd(msh);
	create_pipes_for_hd(msh);
	scan_cmd_nature(msh);
	feed_msh_acavenvp(msh, ac, av, envp); // sera remplacé par l'env d'Amel
	exec_loop(msh);
	/*
	Peut-être mettre des close finaux
	Ou peut-être que les close dans l'execloop suffisent
	close(ppx->fd_temp);
	close(ppx->pipefd[READ]);
	close(ppx->pipefd[WRITE]);
	*/

	while (waitpid(-1, &(msh->return_value), 0) != -1)
		;
	
}
