/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_args_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:52:27 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:58:00 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	feed_var_names_array(t_msh *msh, char ***raw)
{
	t_env_list	*env_list_node;
	int			i;

	if (msh && msh->env_list)
	{
		env_list_node = msh->env_list;
		i = -1;
		while (env_list_node)
		{
			(*raw)[++i] = ft_strdup(env_list_node->name);
			env_list_node = env_list_node->next;
		}
	}
}

static char	**get_raw_var_name_array(t_msh *msh)
{
	char	**raw;
	int		size_env_list;

	raw = NULL;
	if (msh && msh->env_list)
	{
		size_env_list = get_size_env_list(msh);
		raw = malloc_full_null_charss(size_env_list);
		feed_var_names_array(msh, &raw);
	}
	return (raw);
}

static t_bool	next_smaller_than_current(char **sorted_var_names_array, int i)
{
	char	*current;
	char	*next;
	int		j;
	t_bool	ret;

	current = ft_strdup(sorted_var_names_array[i]);
	next = ft_strdup(sorted_var_names_array[i + 1]);
	j = -1;
	while (current[++j] && current[j] == next[j])
		;
	if (next[j] < current[j])
		ret = TRUE;
	else
		ret = FALSE;
	free_chars(&(current));
	free_chars(&(next));
	return (ret);
}

static void	export_swap(char ***sorted_var_names_array, int i)
{
	char	*current;
	char	*next;

	current = ft_strdup((*sorted_var_names_array)[i]);
	next = ft_strdup((*sorted_var_names_array)[i + 1]);
	free_chars(&((*sorted_var_names_array)[i]));
	free_chars(&((*sorted_var_names_array)[i + 1]));
	(*sorted_var_names_array)[i] = ft_strdup(next);
	(*sorted_var_names_array)[i + 1] = ft_strdup(current);
	free_chars(&current);
	free_chars(&next);
}

char	**get_sorted_var_names_array(t_msh *msh)
{
	char	**sorted_var_names_array;
	t_bool	swap;
	int		i;
	int		size_array;

	sorted_var_names_array = get_raw_var_name_array(msh);
	size_array = get_size_ntcharss(sorted_var_names_array);
	swap = TRUE;
	while (swap)
	{
		swap = FALSE;
		i = -1;
		while (++i < size_array - 1)
		{
			if (next_smaller_than_current(sorted_var_names_array, i))
			{
				swap = TRUE;
				export_swap(&sorted_var_names_array, i);
			}
		}
	}
	return (sorted_var_names_array);
}
