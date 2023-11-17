#include "minishell.h"

static int print = 0;

t_bool	exists_in_paths(t_msh *msh, t_exec_list *exec_list_node)
{
	if (print) {dprintf(2, "exists_in_paths : Entrée\n");}
	if (print) {print_charss(msh->exec->paths_from_path);}
	char	*abs_path_candidate;
	int		i;

	abs_path_candidate = NULL;
	i = -1;
	if (msh && msh->exec && msh->exec->paths_from_path && exec_list_node)
	{
		while (msh->exec->paths_from_path[++i])
		{
			abs_path_candidate = ft_strjoin(msh->exec->paths_from_path[i],
				exec_list_node->cmd);
			if (print) {dprintf(2, "exists_in_paths : abs_path_candidate = %s\n", abs_path_candidate);}
			if (!access(abs_path_candidate, X_OK))
			{
				msh->exec->cmd_path_ready = ft_strdup(abs_path_candidate);
				free_chars(&abs_path_candidate);
				return (TRUE);
			}
			free_chars(&abs_path_candidate);
		}
		free_chars(&abs_path_candidate);
	}
	if (print) {dprintf(2, "exists_in_paths : Return imminent\n");}
	return (FALSE);
}

int	get_index_last_slash(char *cmd_with_path)
{
	int	i;
	int	index_last_slash;

	i = -1;
	index_last_slash = 0;
	if (cmd_with_path)
	{
		while (cmd_with_path[++i])
		{
			if (cmd_with_path[i] == '/')
				index_last_slash = i;
		}
	}
	return (index_last_slash);
}

int	get_size_cmd(char *cmd_with_path, int index)
{
	int	size;

	size = 0;
	if (cmd_with_path)
	{
		while (cmd_with_path[++index])
			size++;
	}
	return (size);
}

void	get_cmd_without_path_in_args(t_msh *msh, t_exec_list *exec_list_node)
{
	int		index_last_slash;

	if (print) {if (print) {dprintf(2, "get_cmd_without_path_in_args : cmd_with_path = %s\n", exec_list_node->args_array[0]);}}
	if (msh && msh->exec && exec_list_node && exec_list_node->args_array)
	{
		index_last_slash = get_index_last_slash(msh->exec->cmd_path_ready);
		free_chars(&(exec_list_node->args_array[0]));
		exec_list_node->args_array[0] = ft_substr(msh->exec->cmd_path_ready,
			index_last_slash + 1, ft_strlen(msh->exec->cmd_path_ready));
	}
	if (print) {if (print) {dprintf(2, "get_cmd_without_path_in_args : cmd_without_path = %s\n", exec_list_node->args_array[0]);}}
}

void	print_cmd_not_found_errormsg(char *cmdnf)
{
	//ft_putstr_fd("minishell: (print_cmd_not_found_errormsg) ", 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmdnf, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	check_cmd_path_n_exec(t_msh *msh, t_exec_list *exec_list_node)
{
	if (msh && msh->exec_list && exec_list_node)
	{
		msh->exec->cmd_path_ready = ft_strdup(exec_list_node->cmd);
		if (!access(exec_list_node->cmd, X_OK))
		{
			if (print) {dprintf(2, "check_cmd_path_n_exec : entrée dans le premier if\n");}
			get_cmd_without_path_in_args(msh, exec_list_node);
			ft_execve(msh, exec_list_node);
		}
		//exists_in_paths assigne msh->exec->cmd_path_ready si succès
		if (exists_in_paths(msh, exec_list_node))
		{
			if (print) {dprintf(2, "check_cmd_path_n_exec : entrée dans le deuxième if\n");}
			ft_execve(msh, exec_list_node);
		}
		if (exec_list_node->cmd)
			print_cmd_not_found_errormsg(exec_list_node->cmd);
	}
	exit(EXIT_FAILURE);
}
