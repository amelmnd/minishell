/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:49:43 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:59:11 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print(t_msh *msh, char **sorted_var_names_array)
{
	int		i;
	char	*var_value;

	if (sorted_var_names_array)
	{
		i = -1;
		while (sorted_var_names_array[++i])
		{
			if (ft_strlen(sorted_var_names_array[i]) > 1
				|| sorted_var_names_array[i][0] != '_')
			{
				var_value = msh_getenv(msh, sorted_var_names_array[i]);
				printf("declare -x %s", sorted_var_names_array[i]);
				if (var_value)
					printf("=\"%s\"", var_value);
				printf("\n");
				free_chars(&var_value);
			}
		}
	}
}

void	export_without_args(t_msh *msh)
{
	char	**sorted_var_names_array;

	if (msh && msh->env_list)
	{
		sorted_var_names_array = get_sorted_var_names_array(msh);
		export_print(msh, sorted_var_names_array);
		free_ntcharss(&(sorted_var_names_array));
	}
}
