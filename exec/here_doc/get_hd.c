/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:17:30 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/08 08:33:41 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	hd_strcmp(char *limiter, char *line)
{
	char	*limiter_with_nl;
	t_bool	return_value;

	return_value = FALSE;
	if (limiter && line)
	{
		limiter_with_nl = ft_strjoin(limiter, "\n");
		if (limiter_with_nl)
		{
			if (ft_strcmp(limiter_with_nl, line))
				return_value = TRUE;
			else
				return_value = FALSE;
			free(limiter_with_nl);
		}
	}
	return (return_value);
}

void	get_hd(t_exec_list *exec_list_node, int i)
{
	char	*line;
	int		j;

	line = NULL;
	j = 0;
	if (exec_list_node && exec_list_node->redirect_array
		&& exec_list_node->redirect_array[i].str && exec_list_node->hd)
	{
		while (42)
		{
			//dev
			/*
			write(STDOUT_FILENO, exec_list_node->redirect_array[i].str, ft_strlen(exec_list_node->redirect_array[i].str));
			write(STDOUT_FILENO, "(", 1);
			write_the_proper_number(ft_strlen(exec_list_node->redirect_array[i].str));
			write(STDOUT_FILENO, ")", 1);
			*/
			write(STDOUT_FILENO, " > ", 2);
			line = get_next_line(STDIN_FILENO);
			if (hd_strcmp(exec_list_node->redirect_array[i].str, line))
				break ;
			if (j)
				feed_append_new_hd_node(exec_list_node, line);
			else
				exec_list_node->hd->str = ft_strdup(line);
			free_chars(&line);
			j++;
		}
	}
	free_chars(&line);
}