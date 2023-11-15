/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:53:18 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:59:54 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inv_ident_errormsg(t_msh *msh, char *str)
{
	if (msh)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		msh->return_code = 1;
	}
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
			var_name = export_get_var_name(exec_list_node->args_array[i]);
			if (is_a_valid_identifier(var_name))
				add_var_to_env_list(msh, var_name,
					exec_list_node->args_array[i]);
			else
				inv_ident_errormsg(msh, exec_list_node->args_array[i]);
			free_chars(&var_name);
		}
	}
}
