#include "minishell.h"

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

/*
t_bool	check_valid_cmd_abs_path(t_msh *msh, char *cmd)
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

*/

t_bool	ft_access(t_msh *msh, char *path)
{

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
	if (ft_access(msh, exec_list_node->cmd))
		ft_execve(msh, exec_list_node);
	if (exists_in_paths(msh, exec_list_node))
	/*
	si exec_list_node->cmd est un nom de fichier existant dans les paths
	ft_execve()
	nsfod_msg()
	exit(EXIT_FAILURE);

	*/

}

/*
si exec_list_node->cmd est un path pour lequel acces renvoie 0 :
	packés dans une fonction (ft_execve() ?)
	{
		execve (exit si aucun problème, renvoie -1 avec errno défini s'il y a un problème)
		perror("execve");
		exit(EXIT_FAILURE);
	}
si exec_list_node->cmd est un nom de fichier existant dans les paths
	ft_execve()
nsfod_msg()
exit(EXIT_FAILURE);

*/
