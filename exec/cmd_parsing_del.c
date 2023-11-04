#include "minishell.h"

t_bool	exists_in_paths(t_msh *msh, t_exec_list *exec_list_node)
{
	//printf("exists_in_paths : Entrée\n");
	//print_charss(msh->exec->paths_from_path);
	char	*abs_path_candidate;
	int		i;

	abs_path_candidate = NULL;
	i = -1;
	while (msh->exec->paths_from_path[++i])
	{
		abs_path_candidate = ft_strjoin(msh->exec->paths_from_path[i],
			exec_list_node->cmd);
		//printf("exists_in_paths : abs_path_candidate = %s\n", abs_path_candidate);
		if (!access(abs_path_candidate, X_OK))
		{
			msh->exec->cmd_path_ready = ft_strdup(abs_path_candidate);
			free_chars(&abs_path_candidate);
			return (TRUE);
		}
		free_chars(&abs_path_candidate);
	}
	free_chars(&abs_path_candidate);
	//printf("exists_in_paths : Return imminent\n");
	return (TRUE);
}

void ft_execve(t_msh *msh, t_exec_list *exec_list_node)
{
	//(void)exec_list_node;
	t_exec	*exec;

	exec = msh->exec;
	printf("ft_execve : Entrée\n");
	//printf("ft_execve : exec->cmd_path_ready = %s\n", exec->cmd_path_ready);
	//printf("ft_execve : exec_list_node->args_array[0] = %s ; exec_list_node->args_array[1] = %s\n", exec_list_node->args_array[0], exec_list_node->args_array[1]);
	execve(exec->cmd_path_ready, exec_list_node->args_array, exec->envp);

	printf("ft_execve : après le execve ; perror puis exit imminent\n");

	perror("execve");
	exit(EXIT_FAILURE);
}

int	get_index_last_slash(char *cmd_with_path)
{
	int	i;
	int	index_last_slash;

	i = -1;
	index_last_slash = 0;
	while (cmd_with_path[++i])
	{
		if (cmd_with_path[i] == '/')
			index_last_slash = i;
	}
	return (index_last_slash);
}

int	get_size_cmd(char *cmd_with_path, int index)
{
	int	size;

	size = 0;
	while (cmd_with_path[++index])
		size++;
	return (size);
}

void	get_cmd_without_path_in_args(t_msh *msh, t_exec_list *exec_list_node)
{
	//printf("get_cmd_without_path_in_args : cmd_with_path = %s\n", exec_list_node->args_array[0]);

	int		index_last_slash;

	index_last_slash = get_index_last_slash(msh->exec->cmd_path_ready);
	free_chars(&(exec_list_node->args_array[0]));
	exec_list_node->args_array[0] = ft_substr(msh->exec->cmd_path_ready,
		index_last_slash + 1, ft_strlen(msh->exec->cmd_path_ready));
	
	//printf("get_cmd_without_path_in_args : cmd_without_path = %s\n", exec_list_node->args_array[0]);
}

void	check_cmd_path_n_exec(t_msh *msh, t_exec_list *exec_list_node)
{
	msh->exec->cmd_path_ready = ft_strdup(exec_list_node->cmd);
	if (!access(exec_list_node->cmd, X_OK))
	{
		printf("check_cmd_path_n_exec : entrée dans le premier if\n");
		get_cmd_without_path_in_args(msh, exec_list_node);
		ft_execve(msh, exec_list_node);
	}
	if (exists_in_paths(msh, exec_list_node)) // assigne msh->exec->cmd_path_ready si succès
	{
		printf("check_cmd_path_n_exec : entrée dans le deuxième if\n");
		ft_execve(msh, exec_list_node);
		//nsfod_msg();
		exit(EXIT_FAILURE);
	}
	perror("access");
	exit(EXIT_FAILURE);
}
