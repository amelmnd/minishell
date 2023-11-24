/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:04:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/23 16:49:48 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// à nettoyer

t_env_list	*new_env_list(void)
{
	t_env_list	*new;

	new = NULL;
	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->next = NULL;
	new->previous = NULL;
	new->value = NULL;
	return (new);
}

int	get_index_first_equal(char *str)
{
	int	index_first_equal;

	index_first_equal = -1;
	while (str && str[++index_first_equal])
	{
		if (str[index_first_equal] == '=')
			return (index_first_equal);
	}
	return (0);
}

char	*get_name_var(char *var_n_value)
{
	char	*name_var;
	int		index_first_equal;
	int		i;

	name_var = NULL;
	index_first_equal = get_index_first_equal(var_n_value);
	if (index_first_equal == -1)
		return (NULL);
	name_var = (char *)malloc(sizeof(char) * (index_first_equal + 1));
	if (!name_var)
		return (NULL);
	i = -1;
	while (var_n_value[++i] != '=')
		name_var[i] = var_n_value[i];
	name_var[index_first_equal] = '\0';
	return (name_var);
}

int	get_value_size(char *var_n_value)
{
	return (ft_strlen(var_n_value) - get_index_first_equal(var_n_value) - 1);
}

char	*get_value_var(char *var_n_value)
{
	char	*value_var;
	int		value_size;
	int		i;
	int		j;

	value_var = NULL;
	value_size = get_value_size(var_n_value);
	value_var = (char *)malloc(sizeof(char) * value_size + 1);
	if (!value_var)
		return (NULL);
	i = 0;
	j = get_index_first_equal(var_n_value);
	while (var_n_value[++j])
		value_var[i++] = var_n_value[j];
	value_var[value_size] = '\0';
	return (value_var);
}

void	feed_env_list_node(t_env_list *env_list_node, char *var_n_value)
{
	char	*name_var;
	char	*value_var;

	name_var = get_name_var(var_n_value);
	value_var = get_value_var(var_n_value);
	env_list_node->name = ft_strdup(name_var);
	env_list_node->value = ft_strdup(value_var);
	free_chars(&name_var);
	free_chars(&value_var);
	/*
	Nico : il y a peut-être moyen de faire plus simple (c'est mon code) :
	env_list_node->name = get_name_var(var_n_value);
	env_list_node->value = get_value_var(var_n_value);
	*/
}

void	fill_first_env_list_node(t_msh *msh, char *var_n_value)
{
	t_env_list	*first_env_list_node;

	first_env_list_node = msh->env_list;
	feed_env_list_node(first_env_list_node, var_n_value);
}

void	append_new_fed_list_node(t_msh *msh, char *var_n_value)
{
	t_env_list	*last_env_list_node;
	t_env_list	*new_env_list_node;

	last_env_list_node = msh->env_list;
	new_env_list_node = new_env_list();
	while (last_env_list_node->next)
		last_env_list_node = last_env_list_node->next;
	last_env_list_node->next = new_env_list_node;
	new_env_list_node->previous = last_env_list_node;
	feed_env_list_node(new_env_list_node, var_n_value);
}

void	env_list_generate(t_msh *msh, char *envp[])
{
	int	i;

	i = -1;
	if (msh)
	{
		if (envp)
			msh->env_list = new_env_list();
		while (envp && envp[++i])
		{
			if (!i)
				fill_first_env_list_node(msh, envp[i]);
			else
				append_new_fed_list_node(msh, envp[i]);
		}
	}
}