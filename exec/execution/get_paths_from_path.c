/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_from_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:23:40 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 12:23:41 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_slash_to_paths(t_msh *msh)
{
	char	*unslashed_path;
	int		i;

	unslashed_path = NULL;
	i = -1;
	while (msh->exec->paths_from_path[++i])
	{
		unslashed_path = ft_strdup(msh->exec->paths_from_path[i]);
		free_chars(&(msh->exec->paths_from_path[i]));
		msh->exec->paths_from_path[i] = ft_strjoin(unslashed_path, "/");
		free_chars(&unslashed_path);
	}
}

static void	get_path_from_mshenv(t_msh *msh)
{
	char	*temp;
	int		i;
	
	temp = NULL;
	i = 0;
	while (msh->msh_env[i] && ft_strncmp(msh->msh_env[i], "PATH=", 5))
		i++;
	if (!(msh->msh_env[i]))
		msh->exec->path_defined = FALSE;
	else if (!ft_strncmp(msh->msh_env[i], "PATH=", 5))
	{
		temp = ft_strdup(msh->msh_env[i]);
		msh->exec->path_from_mshenv = ft_substr(temp, 5, ft_strlen(temp));
		msh->exec->path_defined = TRUE;
	}
	else
		msh->exec->path_defined = FALSE;
	free_chars(&temp);
}

void	get_paths_from_path(t_msh *msh)
{
	get_path_from_mshenv(msh);
	if (msh->exec->path_from_mshenv)
		msh->exec->paths_from_path = ft_split(msh->exec->path_from_mshenv,
			':');
	append_slash_to_paths(msh);
}
