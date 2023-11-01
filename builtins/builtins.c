#include "minishell.h"

int	is_a_builtin(char *exec_list_node_cmd)
{
	if (ft_strcmp(exec_list_node_cmd, "echo")
		|| ft_strcmp(exec_list_node_cmd, "/bin/echo"))
		return (1);
	else if (ft_strcmp(exec_list_node_cmd, "cd"))
		return (2);
	else if (ft_strcmp(exec_list_node_cmd, "pwd"))
		return (3);
	else if (ft_strcmp(exec_list_node_cmd, "export"))
		return (4);
	else if (ft_strcmp(exec_list_node_cmd, "unset"))
		return (5);
	else if (ft_strcmp(exec_list_node_cmd, "env")
		|| ft_strcmp(exec_list_node_cmd, "/bin/env"))
		return (6);
	else if (ft_strcmp(exec_list_node_cmd, "exit"))
		return (7);
	return (0);
}

int	use_builtin_code(int num_builtin)
{
	if (!num_builtin || num_builtin > 7)
		return (0);
	if (num_builtin == 1)
		echo_builtin();
	else if (num_builtin == 2)
		cd_builtin();
	else if (num_builtin == 3)
		pwd_builtin();
	else if (num_builtin == 4)
		export_builtin();
	else if (num_builtin == 5)
		unset_builtin();
	else if (num_builtin == 6)
		env_builtin();
	else if (num_builtin == 7)
		exit_builtin();
	return (1);
}
