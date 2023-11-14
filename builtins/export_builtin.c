/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:09:57 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/14 01:35:32 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_env_list(t_msh *msh)
{
	int			size;
	t_env_list	*env_list_node;

	size = 0;
	if (msh && msh->env_list)
	{
		env_list_node = msh->env_list;
		while (env_list_node)
		{
			size++;
			env_list_node = env_list_node->next;
		}
	}
	return (size);
}

void	feed_var_names_array(t_msh *msh, char ***sort_var_names_array)
{
	t_env_list	*env_list_node;
	int			i;

	if (msh && msh->env_list)
	{
		env_list_node = msh->env_list;
		i = -1;
		while (env_list_node)
		{
			(*sort_var_names_array)[++i] = ft_strdup(env_list_node->name);
			env_list_node = env_list_node->next;
		}
	}
}

int	export_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

void	sort_var_names_array(char ***sorted_var_names_array, int size)
{
	char	**arr;
	char	*temp;
	int		i;
	int		j;

	arr = *sorted_var_names_array;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - i)
		{
			if (export_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

char	**get_sorted_var_names_array(t_msh *msh)
{
	int		size_env_list;
	char	**sorted_var_names_array;

	sorted_var_names_array = NULL;
	if (msh && msh->env_list)
	{
		size_env_list = get_size_env_list(msh);
		sorted_var_names_array = malloc_full_null_charss(size_env_list);
		feed_var_names_array(msh, &sorted_var_names_array);
		sort_var_names_array(&sorted_var_names_array, size_env_list);
	}
	return (sorted_var_names_array);
}

void	print_sorted_var_names_array(t_msh *msh, char **sorted_var_names_array)
{
	int	i;

	if (sorted_var_names_array)
	{
		i = -1;
		while (sorted_var_names_array[++i])
		{
			printf("declare -x %s", sorted_var_names_array[i]);
			printf("\"%s\"\n", msh_getenv(msh, sorted_var_names_array[i]));
		}
	}
}

void	print_env_list_export_way(t_msh *msh)
{
	char	**sorted_var_names_array;

	if (msh && msh->env_list)
	{
		sorted_var_names_array = get_sorted_var_names_array(msh);
		print_sorted_var_names_array(msh, sorted_var_names_array);
		free_ntcharss(&(sorted_var_names_array));
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//partie export avec argument

t_bool	var_already_exists(t_msh *msh, char *var_name)
{
	t_env_list	*env_list_node;

	if (msh && msh->env_list && var_name)
	{
		env_list_node = msh->env_list;
		while (env_list_node)
		{
			if (ft_strcmp(env_list_node->name, var_name))
				return (TRUE);
			env_list_node = env_list_node->next;
		}
	}
	return (FALSE);
}

int	is_c_in_s(char *s, char c)
{
	int	i;
	
	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (0);
}

char	*get_var_value(char *var_name, char *arg)
{
	int		index_equal;
	char	*var_value;
	int		size_var_value;
	int		i;

	index_equal = is_c_in_s(arg, '=');
	var_value = NULL;
	if (index_equal)
	{
		size_var_value = ft_strlen(arg) - ft_strlen(var_name) - 1;
		var_value = (char *)malloc(sizeof(char) * (size_var_value + 1));
		i = -1;
		while (++i < size_var_value)
			var_value[i] = arg[index_equal + 1 + i];
		var_value[size_var_value] = '\0';
		return (var_value);
	}
	return (ft_strdup(""));
}

void	update_variable(t_msh *msh, char var_name, char *arg)
{
	char		*var_value;
	t_env_list	*env_list_node;

	if (msh && msh->env_list && var_name)
	{
		var_value = get_var_value(var_name, arg);
		env_list_node = msh->env_list;
		while (env_list_node)
		{
			if (ft_strcmp(env_list_node->next, var_name))
			{
				free_chars(&(env_list_node->value));
				env_list_node->value = ft_strdup(var_value);
				free_chars(&(var_value));
				return ;
			}
			env_list_node = env_list_node->next;
		}
		free_chars(&(var_value));
	}
}

void	add_new_couple_name_value(t_msh *msh, char *var_name, char *arg)
{
	t_env_list	*new_env_list_node;
	t_env_list	*last_env_list_node;

	new_env_list_node = NULL;
	last_env_list_node = NULL;
	if (msh && msh->env_list && var_name)
	{
		new_env_list_node = new_env_list();
		new_env_list_node->name = ft_strdup(var_name);
		new_env_list_node->value = get_var_value(var_name, arg);
		last_env_list_node = msh->env_list;
		while (last_env_list_node->next)
			last_env_list_node = last_env_list_node->next;
		last_env_list_node->next = new_env_list_node;
		new_env_list_node->previous = last_env_list_node;
	}
}

void	add_var_to_env_list(t_msh *msh, char *var_name, char *arg)
{
	if (msh && msh->env_list && var_name && arg)
	{
		if (var_already_exists(msh, var_name))
			update_variable(msh, var_name, arg);
		else
			add_new_couple_name_value(msh, var_name, arg);
	}
}

t_bool	is_not_a_valid_chr(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (FALSE);
	return (TRUE);
}

t_bool	is_a_valid_identifier(char *var_name)
{
	char	*name_var;
	int		i;

	if (ft_strlen(var_name))
	{
		if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
			return (FALSE);
		i = 0;
		while (var_name[++i])
		{
			if (is_not_a_valid_chr(var_name[i]))
				return (FALSE);
		}
		return (TRUE);
	}
	else 
		return (FALSE);
}

void inv_ident_errormsg(t_msh *msh, char *str)
{
	if (msh)
	{
		printf("minishell: export: `");
		printf("%s", str);
		printf("': not a valid identifier\n");
		msh->return_code = 1;
	}
}

int	get_size_var_name(char *arg)
{
	int	size;
	int	i;

	size = 0;
	if (arg)
	{
		i = -1;
		while (arg[++i] && arg[i] != '=')
			size++;
	}
	return (size);
}

char	*get_var_name(char *arg)
{
	char	*var_name;
	int		size_var_name;
	int		i;

	var_name = NULL;
	if (arg)
	{
		size_var_name = get_size_var_name(arg);
		var_name = (char *)malloc(sizeof(char) * (size_var_name + 1));
		if (!var_name)
			return (NULL);
		i = -1;
		while (++i < size_var_name)
			var_name[i] = arg[i];
		var_name[i] = '\0';
	}
	return (var_name);
}

void	export_with_args(t_msh *msh, t_exec_list *exec_list_node)
{
	int		i;
	char	*var_name;

	var_name = NULL;
	if (msh && exec_list_node && exec_list_node->args_array)
	{
		i = 0;
		while (++i < exec_list_node->nb_words)
		{
			var_name = get_var_name(exec_list_node->args_array[i]);
			if (is_a_valid_identifier(var_name))
				add_var_to_env_list(msh, var_name,
					exec_list_node->args_array[i]);
			else
				inv_ident_errormsg(msh, exec_list_node->args_array[i]);
			free_chars(&var_name);
		}
	}
}

void	export_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	if (msh && exec_list_node)
	{
		if (exec_list_node->nb_words == 1)
			print_env_list_export_way(msh);
		else
			export_with_args(msh, exec_list_node);
	}
}
