/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:24:25 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/17 18:08:54 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	ft_flag_n_cmp(char *s1)
{
	int	i;

	i = 0;
	if (s1[i] != '-')
		return (0);
	i++;
	while (s1[i])
	{
		if (s1[i] != 'n')
		{
			free_chars(&s1);
			return (0);
		}
		i++;
	}
	free_chars(&s1);
	return (1);
}

void	echo_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	int		i;
	t_bool	n_flag;
	int		array_size;
	int		compare;

	(void)msh;
	i = 1;
	n_flag = FALSE;
	array_size = ft_array_size(exec_list_node->args_array);
	compare = ft_flag_n_cmp(exec_list_node->args_array[1]);
	if (compare)
		n_flag = TRUE;
	while (ft_flag_n_cmp(exec_list_node->args_array[i]))
		i++;
	while (exec_list_node->args_array[i])
	{
		printf("%s", exec_list_node->args_array[i]);
		if (i < array_size - 1)
			printf(" ");
		i++;
	}
	if (n_flag == FALSE)
		printf("\n");
}
