#include "minishell.h"

static int print = 0;

void	exec_loop(t_msh *msh)
{
	static int nb_function_call = 0;
	if (print) {dprintf(2, "exec_loop (appel numéro : %d) : Entrée\n", nb_function_call);}
	nb_function_call++;
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	int j = 0;
	while (exec_list_node)
	{
		if (exec_list_node->pos_ppl != SOLO)
			pipe(msh->exec->pipefd);
		ft_fork(msh);
		if (!(msh->exec->child))
		{
			if (print) {dprintf(2, "\nPROCESSUS numéro %d\n", j);}
			do_all_redirections(msh, exec_list_node, j);

			//close_all_fd();

			//builtin_way(msh, exec_list_node);
			
			check_cmd_path_n_exec(msh, exec_list_node);
		}
		send_hd_through_pipe(exec_list_node, j); // attention aux builtin solo qui ne fork pas

		if (exec_list_node->pos_ppl == MIDDLE || exec_list_node->pos_ppl == LAST)
			close(msh->exec->fd_temp);
		
		if (exec_list_node->pos_ppl == FIRST || exec_list_node->pos_ppl == MIDDLE)
			msh->exec->fd_temp = dup(msh->exec->pipefd[READ]);
		
		if (exec_list_node->pos_ppl != SOLO)
		{
			close(msh->exec->pipefd[READ]);
			close(msh->exec->pipefd[WRITE]);
		}

		exec_list_node = exec_list_node->next;
		j++;
		sleep(1);
	}
}

void execution(t_msh *msh, char **envp)
{
	msh->exec = new_exec();
	init_exec(msh);

	get_all_hd_content(msh);
	mark_all_erased_hd(msh);

	// ATTENTION !!!!
	feed_msh_with_envp(msh, envp); // il faut récupérer l'env_list et la convertir en char **
	// pour enfin l'assigner (malloc) à msh->exec->envp

	create_pipes_for_hd(msh); // attention aux builtin solo qui ne forkent pas
	//print_charss(msh->exec->envp);
	//print_exec_list(msh);

	/*
	if (msh->exec_list->pos_ppl != SOLO)
		msh->exec->fd_temp = open(".temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	*/
	
	exec_loop(msh);
	
	/*
	if (access(".temp", 0644))
		unlink(".temp"); // a placer dans les fonctions de free
	*/
	

	//Peut-être mettre des close finaux;
	//Ou peut-être que les close dans l'execloop suffisent;
	
	if (msh->exec_list->nb_pipes)
		close(msh->exec->fd_temp);
	//close(ppx->pipefd[READ]);
	//close(ppx->pipefd[WRITE]);

	
	while (waitpid(-1, &(msh->return_code), 0) != -1)
		;
	
}


// version chatpgt

/*
#include "minishell.h"

void exec_loop(t_msh *msh)
{
	t_exec_list *exec_list_node;
	exec_list_node = msh->exec_list;
	int j = 0;
	while (exec_list_node)
	{
		pipe(msh->exec->pipefd);
		ft_fork(msh);
		if (!(msh->exec->child))
		{
			if (print) {dprintf(2, "\nPROCESSUS numéro %d\n", j);}
			do_all_redirections(msh, exec_list_node, j);

			close(msh->exec->pipefd[READ]);
			close(msh->exec->fd_temp);

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

void execution(t_msh *msh, char **envp)
{

	msh->exec = new_exec();
	init_exec(msh);

	get_all_hd_content(msh);
	mark_all_erased_hd(msh);
	feed_msh_with_envp(msh, envp); // différent du path d'Amel, sous la forme d'une liste chainée
	// cette fonction reste nécessaire, même avec le travail d'Amel
	create_pipes_for_hd(msh);
	//print_charss(msh->exec->envp);
	//print_exec_list(msh);
	exec_loop(msh);
	

	//Peut-être mettre des close finaux;
	//Ou peut-être que les close dans l'execloop suffisent;
	//close(ppx->fd_temp);
	//close(ppx->pipefd[READ]);
	//close(ppx->pipefd[WRITE]);

	
	while (waitpid(-1, &(msh->return_code), 0) != -1)
		;
	
}
*/