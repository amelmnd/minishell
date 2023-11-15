/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_msh_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:03:55 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 08:54:14 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//minishell tourne avec son propre environnement  grâce à, entre autres, ces fonctions

static int	get_size_env_list(t_msh *msh)
{
	int			size;
	t_env_list	*env_list;

	size = 0;
	if (msh && msh->env_list)
	{
		env_list = msh->env_list;
		while (env_list)
		{
			env_list = env_list->next;
			size++;
		}
	}
	return (size);
}

static char	*join_var_equal_value(t_env_list *env_list)
{
	int		total_size;
	char	*join;
	int		i;
	int		j;

	join = NULL;
	if (env_list)
	{
		total_size = ft_strlen(env_list->name)
			+ ft_strlen(env_list->value) + 2;
		join = (char *)malloc(sizeof(char) * (total_size));
		if (!join)
			return (NULL);
		i = -1;
		while (env_list->name[++i])
			join[i] = env_list->name[i];
		join[i] = '=';
		j = -1;
		while (env_list->value[++j])
			join[i + j + 1] = env_list->value[j];
		join[i + j + 1] = '\0';
	}
	return (join);
}

void	generate_msh_env(t_msh *msh)
{
	t_env_list	*env_list;
	int			i;

	if (msh && msh->env_list)
	{
		env_list = msh->env_list;
		msh->msh_env = malloc_full_null_charss(get_size_env_list(msh));
		if (!(msh->msh_env))
			return ;
		i = -1;
		while (env_list)
		{
			if (env_list->value)
				msh->msh_env[++i] = join_var_equal_value(env_list);
			env_list = env_list->next;
		}
	}
}
