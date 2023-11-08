#include "minishell.h"

void	exec_loop(t_msh *msh)
{
	static int nb_function_call = 0;
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
			do_all_redirections(msh, exec_list_node, j);

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
	get_all_hd_content(msh);
	mark_all_erased_hd(msh);

	// ATTENTION !!!!
	feed_msh_with_envp(msh, envp); // il faut récupérer l'env_list et la convertir en char **
	// pour enfin l'assigner (malloc) à msh->exec->envp

	create_pipes_for_hd(msh); // attention aux builtin solo qui ne forkent pas

	/*
	if (builtin_solo_needs_not_to_fork(msh))
		builtin_solo_without_fork(msh);
	else
	{
		create_pipes_for_hd(msh);
		exec_loop(msh);
		if (msh->exec_list->nb_pipes)
			close(msh->exec->fd_temp);
		while (waitpid(-1, &(msh->return_code), 0) != -1)
			;
		// il faut récupérer les codes d'exit pour assigner la valeur de retour
	}
	*/

	exec_loop(msh);

	//Peut-être mettre des close finaux;
	//Ou peut-être que les close dans l'execloop suffisent;
	// vérifier avec lsof
	
	if (msh->exec_list->nb_pipes)
		close(msh->exec->fd_temp);

	while (waitpid(-1, &(msh->return_code), 0) != -1)
		;
	// il faut récupérer les codes d'exit pour assigner la valeur de retour
}
