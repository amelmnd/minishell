#include "minishell.h"

// à supprimer à terme
// à intégrer à un dev.h pour le moment peut-être ?
void	print_pid_t_array(t_msh *msh)
{
	int	size_pid_t_array;
	int	i;

	if (msh && msh->exec && msh->exec_list)
	{
		size_pid_t_array = msh->exec_list->nb_pipes + 1;
		i = -1;
		while (++i < size_pid_t_array)
			dprintf(2, "[%d] ", msh->exec->pid_t_array[i]);
		dprintf(2, "\n");
	}
}

void	exec_loop(t_msh *msh)
{
	//dprintf(2, "exec_loop ; Entrée\n");
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

			builtin_way(msh, exec_list_node);
			//dprintf(2, "exec_loop ; entrée dans le processus enfant\n");
			// la fonction builtin_way contient un exit
			// les builtins en eux_mêmes ne contiennent pas d'exit
			check_cmd_path_n_exec(msh, exec_list_node); // contient tous les exit
		}
		msh->exec->pid_t_array[j] = msh->exec->child; //à réactiver pour tester
		if (exec_list_node->pos_ppl == SOLO || exec_list_node->pos_ppl == LAST)
			msh->exec->last_child = msh->exec->child;
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
		sleep(1); // à supprimer à terme
	}
	//print_pid_t_array(msh);
}

// récupérer la version printée de chatgpt pour mieux comprendre cette fonction
void	wait_and_get_the_last_return_code(t_msh *msh)
{
	int		status;
	pid_t	pid;
	int		last_exit_status;

	if (msh && msh->exec)
	{
		pid = waitpid(-1, &status, 0);
		while (pid != -1)
		{
			if (WIFEXITED(status))
			{
				if (pid == msh->exec->last_child)
					last_exit_status = WEXITSTATUS(status);
			}
			pid = waitpid(-1, &status, 0);
		}
		msh->return_code = last_exit_status;
		//printf("wait_and_get_the_last_return_code : msh->return_code = %d\n", msh->return_code); // à supprimer à terme
	}
}

void	create_pid_t_array(t_msh *msh)
{
	int	nb_childs;

	if (msh && msh->exec && msh->exec_list)
	{
		nb_childs = msh->exec_list->nb_pipes + 1;
		msh->exec->pid_t_array = (pid_t *)malloc(sizeof(pid_t) * nb_childs);
		if (!(msh->exec->pid_t_array))
			return ;
		while (--nb_childs >= 0)
			msh->exec->pid_t_array[nb_childs] = -1;
	}
}

void execution(t_msh *msh)
{
	//dprintf(2, "execution : Entrée\n");
	//print_exec_list(msh);
	msh->exec = new_exec();
	get_all_hd_content(msh);
	//print_hd_in_exec_list_node(msh->exec_list);
	mark_all_erased_hd(msh);

	get_paths_from_path(msh);

	/*
	// une fois que le bloc de code ci-dessous (actuellement commenté) sera activé
	// cette instruction sera supprimée (car conditionnée dans ledit bloc de code)
	create_pipes_for_hd(msh);
	*/
	// cd ; export ; unset ; exit
	if (no_fork_solo_builtin(msh))
		builtin_solo_without_fork(msh);
	else
	{
		create_pipes_for_hd(msh);
		create_pid_t_array(msh);
		exec_loop(msh);
		if (msh->exec_list->nb_pipes)
			close(msh->exec->fd_temp);
		wait_and_get_the_last_return_code(msh);
		// il faut récupérer les codes d'exit pour assigner la valeur de retour
		// surtout celui du dernier exec_list_node, qui doit permettre d'assigner
		// msh->return_code
	}
	
	//wait_and_get_the_last_return_code(msh);
	// à désactiver quand le bloc de code nfsolobuiltin est activé

	//exec_loop(msh); // à commenter (puis supprimer à terme) quand le bloc ci-dessus
	// (no_fork_solo_builtin) est activé

	//Peut-être mettre des close finaux;
	//Ou peut-être que les close dans l'execloop suffisent;
	// vérifier avec lsof
	if (msh->exec_list->nb_pipes)
		close(msh->exec->fd_temp);
	//dprintf(2, "execution : Sortie\n");
}
