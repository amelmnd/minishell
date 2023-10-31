/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:04:31 by amennad           #+#    #+#             */
/*   Updated: 2023/10/30 16:00:18 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*

int	env_list_is_empty(t_env_list *list)
{
	if (list == NULL)
		return (TRUE);
	return (FALSE);
}

void	env_first_node(t_env_list *node)
{
	node->previous = NULL;
	node->next = NULL;
}

void	env_push_new_node(t_msh *msh, t_env_list *new_node)
{
	t_env_list	*tmp;

	tmp = msh->env_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->previous = tmp;
}

void	env_push(t_msh *msh, char *envp)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return ;
	split_env_value(envp, &new_node->name, &new_node->value);
	if (env_list_is_empty(msh->env_list) == TRUE)
	{
		env_first_node(new_node);
		msh->env_list = new_node;
	}
	else
		env_push_new_node(msh, new_node);
}

void	env_list_generate(t_msh *msh, char *envp[])
{
	int		index;

	index = 0;
	while (envp[index])
	{
		env_push(msh, envp[index]);
		index++;
	}
}
*/

void	print_envp(char **envp)
{
	int i = -1;

	while (envp[++i])
		printf("%s\n", envp[i]);
}

t_env_list	*new_env_list(void)
{
	//printf("new_env_list : Entrée\n");

	t_env_list	*new;

	new = NULL;
	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->next = NULL;
	new->previous = NULL;
	new->value = NULL;
	//printf("new_env_list : return imminent\n");
	return (new);
}

void	free_chars(char **dust)
{
	if (*dust)
	{
		free(*dust);
		*dust = NULL;
	}
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
	return (index_first_equal);
}

char	*get_name_var(char *var_n_value)
{
	//printf("get_name_var : Entrée\n");
	char	*name_var;
	int		index_first_equal;
	int		i;

	name_var = NULL;
	index_first_equal = get_index_first_equal(var_n_value);
	//printf("get_name_var : index_first_equal = %d\n", index_first_equal);
	if (index_first_equal == -1)
		return (NULL);
	name_var = (char *)malloc(sizeof(char) * index_first_equal);
	if (!name_var)
		return (NULL);
	i = -1;
	while (var_n_value[++i] != '=')
		name_var[i] = var_n_value[i];
	name_var[index_first_equal] = '\0';
	//printf("get_name_var : return imminent\n");
	return (name_var);
}

int	get_value_size(char *var_n_value)
{
	return (ft_strlen(var_n_value) - get_index_first_equal(var_n_value) - 1);
}

char	*get_value_var(char *var_n_value)
{
	//printf("get_value_var : Entrée\n");
	char	*value_var;
	int		value_size;
	int		i;
	int		j;

	value_var = NULL;
	value_size = get_value_size(var_n_value);
	//printf("get_value_var : value_size = %d\n", value_size);
	value_var = (char *)malloc(sizeof(char) * value_size + 1);
	if (!value_var)
		return (NULL);
	i = 0;
	j = get_index_first_equal(var_n_value);
	while (var_n_value[++j])
	{
		////printf("get_value_var(while) : var_n_value[i] = %c\n", var_n_value[i]);
		value_var[i++] = var_n_value[j];
	}
	value_var[value_size] = '\0';
	//printf("get_value_var : value_var = %s\n", value_var);
	//printf("get_value_var : return imminent\n");
	return (value_var);
}

void	feed_env_list_node(t_env_list *env_list_node, char *var_n_value)
{
	//printf("feed_env_list_node : Entrée\n");
	char	*name_var;
	char	*value_var;

	name_var = get_name_var(var_n_value);
	value_var = get_value_var(var_n_value);
	//printf("feed_env_list_node : PROBE\n");
	//printf("feed_env_list_node : name_var = %s\n", name_var);
	//printf("feed_env_list_node : value_var = %s\n", value_var);
	//printf("feed_env_list_node : PROBE 2\n");
	env_list_node->name = ft_strdup(name_var);
	env_list_node->value = ft_strdup(value_var);
	free_chars(&name_var);
	free_chars(&value_var);
	//printf("feed_env_list_node : Sortie\n");
}

void	fill_first_env_list_node(t_msh *msh, char *var_n_value)
{
	//printf("fill_first_env_list_node : Entrée\n");
	t_env_list	*first_env_list_node;

	first_env_list_node = msh->env_list;
	feed_env_list_node(first_env_list_node, var_n_value);
	//printf("fill_first_env_list_node : Sortie\n");
}

void	append_new_fed_list_node(t_msh *msh, char *var_n_value)
{
	//printf("append_new_fed_list_node : Entrée\n");
	t_env_list	*last_env_list_node;
	t_env_list	*new_env_list_node;

	last_env_list_node = msh->env_list;
	new_env_list_node = new_env_list();
	while (last_env_list_node->next)
		last_env_list_node = last_env_list_node->next;
	last_env_list_node->next = new_env_list_node;
	new_env_list_node->previous = last_env_list_node;
	feed_env_list_node(new_env_list_node, var_n_value);
	//printf("append_new_fed_list_node : Sortie\n");
}

void	env_list_generate(t_msh *msh, char *envp[])
{
	/*
	(void)msh;
	print_envp(envp);
	*/
	int i = -1;

	if (envp)
		msh->env_list = new_env_list();
	while (envp && envp[++i])
	{
		if (!i)
			fill_first_env_list_node(msh, envp[i]);
		else
			append_new_fed_list_node(msh, envp[i]);
	}
	print_env_list(msh->env_list);
}