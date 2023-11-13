/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:09:57 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/13 18:38:48 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list_export_way(t_msh *msh)
{
	//afficher les variables d'environnement triées par ordre lexicographique
}

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

char	*get_var_value(char *var_name, char *arg)
{
	
}

void	update_variable(t_msh *msh, char var_name, char *arg)
{
	char	*var_value;

	if (msh && msh->env_list && var_name)
	{
		var_value = get_var_value(var_name, arg);


		free_chars(var_value);
	}
}

void	add_var_to_env_list(t_msh *msh, char *var_name, char *arg)
{
	if (msh && var_name && arg)
	{
		if (var_already_exists(msh, var_name));
			update_variable(msh, var_name, arg);
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
