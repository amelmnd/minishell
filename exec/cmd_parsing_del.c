#include "minishell.h"

t_bool	exists_in_paths(t_msh *msh, t_exec_list *exec_list_node)
{
	char	*abs_path_candidate;
	int		i;

	abs_path_candidate = NULL;
	i = -1;
	while (msh->exec->paths_from_path[++i])
	{
		abs_path_candidate = ft_strjoin(msh->exec->paths_from_path[++i],
			exec_list_node->cmd);
		if (!access(abs_path_candidate, X_OK))
		{
			msh->exec->cmd_path_ready = ft_strdup(abs_path_candidate);
			free_chars(abs_path_candidate);
			return (TRUE);
		}
		free_chars(abs_path_candidate);
	}
	free_chars(abs_path_candidate);
	return (TRUE);
}

void ft_execve(t_msh *msh, t_exec_list *exec_list_node)
{
	t_exec	*exec;

	exec = msh->exec;
	execve(exec->cmd_path_ready, exec_list_node->args_array, exec->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	check_cmd_path_n_exec(t_msh *msh, t_exec_list *exec_list_node)
{
	msh->exec->cmd_path_ready = ft_strdup(exec_list_node->cmd);
	if (!access(exec_list_node->cmd, X_OK))
		ft_execve(msh, exec_list_node);
	if (exists_in_paths(msh, exec_list_node)) // assigne msh->exec->cmd_path_ready si succès
	{
		ft_execve(msh, exec_list_node);
		nsfod_msg();
		exit(EXIT_FAILURE);
	}
	perror("access");
	exit(EXIT_FAILURE);
}
