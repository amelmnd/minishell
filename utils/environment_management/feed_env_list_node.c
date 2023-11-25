/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_env_list_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 05:18:09 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/25 05:18:21 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name_var(char *var_n_value)
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

static int	get_value_size(char *var_n_value)
{
	return (ft_strlen(var_n_value) - get_index_first_equal(var_n_value) - 1);
}

static char	*get_value_var(char *var_n_value)
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
	env_list_node->name = get_name_var(var_n_value);
	env_list_node->value = get_value_var(var_n_value);
}
