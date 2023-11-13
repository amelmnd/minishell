/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_prim_env_in_prim_env_list.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:04:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/13 11:58:47 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//les deux fonctions ci-dessous doivent rester solidaires
static void	init_prim_env_list(t_env_list *prim_env_list)
{
	prim_env_list->name = NULL;
	prim_env_list->next = NULL;
	prim_env_list->previous = NULL;
	prim_env_list->value = NULL;
}

t_env_list	*new_env_list(void)
{
	t_env_list	*new;

	new = NULL;
	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	init_prim_env_list(new);
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

void	fill_first_env_list_node(t_msh *msh, char *var_n_value)
{
	t_env_list	*first_env_list_node;

	first_env_list_node = msh->prim_env_list;
	first_env_list_node->name = get_name_var(var_n_value);
	first_env_list_node->value = get_value_var(var_n_value);
}

void	append_new_fed_list_node(t_msh *msh, char *var_n_value)
{
	t_env_list	*last_env_list_node;
	t_env_list	*new_env_list_node;

	last_env_list_node = msh->prim_env_list;
	new_env_list_node = new_env_list();
	while (last_env_list_node->next)
		last_env_list_node = last_env_list_node->next;
	last_env_list_node->next = new_env_list_node;
	new_env_list_node->previous = last_env_list_node;
	new_env_list_node->name = get_name_var(var_n_value);
	new_env_list_node->value = get_value_var(var_n_value);
}

void	retrieve_env_in_env_list(t_msh *msh, char *envp[])
{
	int	i;

	if (msh)
	{
		if (envp)
			msh->prim_env_list = new_env_list();
		i = -1;
		while (envp && envp[++i])
		{
			if (!i)
				fill_first_env_list_node(msh, envp[i]);
			else
				append_new_fed_list_node(msh, envp[i]);
		}
	}
}
