#include "minishell.h"

// partie post fin expander


// partie pré fin expander

/*
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
			
			check_cmd_path_n_exec(msh, exec_list_node);
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
*/

void execution(t_msh *msh, int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	msh->exec = new_exec();
	init_exec(msh);

	get_all_hd_content(msh);
	mark_all_erased_hd(msh);
	create_pipes_for_hd(msh);
	/*
	feed_msh_acavenvp(msh, ac, av, envp); // sera remplacé par l'env d'Amel
	exec_loop(msh);

	Peut-être mettre des close finaux
	Ou peut-être que les close dans l'execloop suffisent
	close(ppx->fd_temp);
	close(ppx->pipefd[READ]);
	close(ppx->pipefd[WRITE]);

	while (waitpid(-1, &(msh->return_value), 0) != -1)
		;
	*/
	
}
