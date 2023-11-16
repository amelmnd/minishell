/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:24:25 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/16 16:24:50 by amennad          ###   ########.fr       */
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
			return (0);
		i++;
	}
	return (1);
}

void	echo_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	// char	*m_error;
	int		i;
	t_bool	n_flag;
	int		array_size;
	int		compare;

	(void)msh;
	i = 1;
	// int y = 1;
	n_flag = FALSE;
	array_size = ft_array_size(exec_list_node->args_array);
	compare = ft_flag_n_cmp(exec_list_node->args_array[1]);
	if (compare)
	{
		n_flag = TRUE;
	}
	while (ft_flag_n_cmp(exec_list_node->args_array[i]))
	{
		i++;
	}
	// if (ft_flag_n_cmp(exec_list_node->args_array[i]) == 0)
	// {
	// 	while (exec_list_node->args_array[i])
	// 	{
	// 		if (!m_error)
	// 			m_error = ft_strdup(exec_list_node->args_array[i]);
	// 		else
	// 			m_error = ft_strjoin(m_error, exec_list_node->args_array[i]);
	// 		if (i < array_size - 1)
	// 			m_error = ft_strjoin(m_error, " ");
	// 		i++;
	// 	}
	// 	exit_command_not_foud(m_error);
	// }
	// else
	// {
		while (exec_list_node->args_array[i])
		{
			printf("%s", exec_list_node->args_array[i]);
			if (i < array_size - 1)
				printf(" ");
			i++;
		}
		if (n_flag == FALSE)
			printf("\n");
	// }
}
