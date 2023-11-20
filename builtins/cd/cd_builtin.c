/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 07:13:15 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/20 10:32:33 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!cwd)
		return (NULL);
	getcwd(cwd, PATH_MAX);
	return (cwd);
}

static char	*set_path_arg(t_msh *msh, t_exec_list *exec_list_node)
{
	char	*path_arg;

	path_arg = NULL;
	if (msh && exec_list_node && exec_list_node->args_array)
	{
		if (exec_list_node->nb_words == 1)
			path_arg = msh_getenv(msh, "HOME");
		else
			path_arg = ft_strdup(exec_list_node->args_array[1]);
	}
	return (path_arg);
}

static void	too_many_args_errmsg(t_msh *msh)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	msh->return_code = 1;
}

static void	generic_cd_errmsg(t_msh *msh, char *path_arg)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(path_arg, 2);
	ft_putstr_fd(" :", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	msh->return_code = 1;
}

void	cd_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	char	*path_arg;
	char	*pwd;
	char	*oldpwd;

	if (msh && msh->env_list && exec_list_node && exec_list_node->cmd)
	{
		path_arg = set_path_arg(msh, exec_list_node);
		pwd = NULL;
		oldpwd = ft_getcwd();
		if (exec_list_node->nb_words > 2)
			too_many_args_errmsg(msh);
		else if (!path_arg[0])
			update_oldpwd_n_pwd(msh, oldpwd, oldpwd);
		else if (chdir(path_arg))
			generic_cd_errmsg(msh, path_arg);
		else
		{
			pwd = ft_getcwd();
			update_oldpwd_n_pwd(msh, oldpwd, pwd);
		}
		free_chars(&path_arg);
		free_chars(&pwd);
		free_chars(&oldpwd);
	}
}
