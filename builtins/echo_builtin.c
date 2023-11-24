/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:24:25 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 20:39:22 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_with_n_flag(t_exec_list *exec_list_node)
{
	int	i;

	i = 1;
	while (++i < exec_list_node->nb_words)
	{
		printf("%s", exec_list_node->args_array[i]);
		if (i < exec_list_node->nb_words - 1)
			printf(" ");
	}
}

static void	echo_without_n_flag(t_exec_list *exec_list_node)
{
	int	i;

	i = 0;
	while (++i < exec_list_node->nb_words)
	{
		printf("%s", exec_list_node->args_array[i]);
		if (i < exec_list_node->nb_words - 1)
			printf(" ");
	}
	printf("\n");
}

void	echo_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	(void)msh;
	if (exec_list_node->nb_words == 1)
		printf("\n");
	else if (ft_strcmp(exec_list_node->args_array[1], "-n"))
		echo_with_n_flag(exec_list_node);
	else
		echo_without_n_flag(exec_list_node);
}
