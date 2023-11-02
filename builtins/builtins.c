#include "minishell.h"

//les builtins doivent contenir les exit appropriés (SUCCESS ou FAILURE)
void	builtin_way(t_msh *msh, t_exec_list *exec_list_node)
{
	if (ft_strcmp(exec_list_node->cmd, "echo")
		|| ft_strcmp(exec_list_node->cmd, "/bin/echo"))
		echo_builtin(msh, exec_list_node);
	else if (ft_strcmp(exec_list_node->cmd, "cd"))
		cd_builtin(msh, exec_list_node);
	else if (ft_strcmp(exec_list_node->cmd, "pwd"))
		pwd_builtin(msh, exec_list_node);
	else if (ft_strcmp(exec_list_node->cmd, "export"))
		export_builtin(msh, exec_list_node);
	else if (ft_strcmp(exec_list_node->cmd, "unset"))
		unset_builtin(msh, exec_list_node);
	else if (ft_strcmp(exec_list_node->cmd, "env")
		|| ft_strcmp(exec_list_node->cmd, "/bin/env"))
		env_builtin(msh, exec_list_node);
	else if (ft_strcmp(exec_list_node->cmd, "exit"))
		exit_builtin(msh, exec_list_node);
}
