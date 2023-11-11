/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 07:13:15 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/11 11:18:42 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Peu importe si le builtin cd est appelé dans un fork ou pas. Le builtin procédera
aux changements des variables d'environnement dans les deux cas.
Dans le cas d'un fork, ces changements n'auront aucun effet (ce qui est voulu)
Dans le cas d'un solo, (le processus parent va donc exécuter le builtin cd),
	le builtin cd va donc changer les variables d'environnement dans la mémoire du
	processus parent ; ces changements vont donc persister (ce qui est voulu)
*/

static char	*set_path_arg(t_msh *msh, t_exec_list *exec_list_node)
{
	char	*path_arg;
	
	path_arg = NULL;
	if (msh && exec_list_node && exec_list_node->args_array)
	{
		if (!(exec_list_node->args_array))
			path_arg = msh_getenv(msh, "HOME");
		else
			path_arg = ft_strdup(exec_list_node->args_array[1]);
		// vérifier s'il ne faut pas rajouter un cas pour assigner correctement path_arg
		// quand l'argument est juste "/"
	}
	return (path_arg);
}

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

void	update_env_list(t_msh *msh, char *name_var, char *new_value)
{
	t_env_list	*env_list_node;

	if (msh && msh->env_list && name_var)
	{
		env_list_node = msh->env_list;
		while (env_list_node)
		{
			if (ft_strcmp(env_list_node->var_name, name_var))
			{
				free_chars(&(env_list_node->var_value));
				env_list_node->var_value = NULL;
				env_list_node->var_value = ft_strdup(new_value);
				return ;
			}
			env_list_node = env_list_node->next;
		}
	}	
}

void	update_oldpwd_n_pwd(t_msh *msh, char *oldpwd, char *pwd)
{
	if (msh && msh->env_list)
	{
		update_env_list(msh, "OLDPWD", oldpwd);
		update_env_list(msh, "PWD", pwd);
		msh->return_code = 0;
	}
}

void	cd_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	char	*path_arg;
	char	*pwd;
	char	*oldpwd;
	
	if (msh && msh->env_list && exec_list_node && exec_lide_node->cmd)
	{
		path_arg = set_path_arg(msh, exec_list_node);
		pwd = NULL;
		oldpwd = ft_getcwd();
		if (!path_arg[0])
			update_oldpwd_n_pwd(msh, oldpwd, oldpwd);
		else if (chdir(path_arg))
			printf("minishell: %s: %s\n", path_arg, strerror(errno));
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

/*
chdir("exec/here_doc/../solo_builtin/../here_doc/../solo_builtin");
	if (access("solo_builtin_del.c", R_OK))
		printf("problem access\n");
	else
	{
		printf("on est bien dans le répertoire solo_builtin\n");
		char *path = (char *)malloc(sizeof(char) * PATH_MAX);
		getcwd(path, PATH_MAX);
		printf("path = %s\n", path);
	}

*/