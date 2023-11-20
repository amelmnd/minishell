/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:17:30 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/20 15:20:58 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_part(t_exec_list *exec_list_node, int i)
{
	char	*line;

	close(exec_list_node->hd_get_pipe[READ]);
	while (42)
	{
		line = readline("> ");
		if (line == NULL)
		{
			close(exec_list_node->hd_get_pipe[WRITE]);
			exit(EXIT_SUCCESS);
		}
		if (ft_strcmp(line, exec_list_node->redir_array[i].str))
		{
			free_chars(&line);
			break ;
		}
		write(exec_list_node->hd_get_pipe[WRITE], line, ft_strlen(line));
		write(exec_list_node->hd_get_pipe[WRITE], "\n", 1);
		free_chars(&line);
	}
	close(exec_list_node->hd_get_pipe[WRITE]);
	exit(EXIT_SUCCESS);
}

static void	parent_part(t_msh *msh, t_exec_list *exec_list_node)
{
	char	buffer[BUFFER_SIZE];
	int		nbytes;
	int		count;

	close(exec_list_node->hd_get_pipe[WRITE]);
	nbytes = read(exec_list_node->hd_get_pipe[READ], buffer, BUFFER_SIZE - 1);
	if (nbytes < 0)
		errmsg_free_exit(msh, "read");
	count = 0;
	while (nbytes > 0)
	{
		buffer[nbytes] = '\0';
		if (count)
			feed_append_new_hd_node(exec_list_node, buffer);
		else
			exec_list_node->hd->str = ft_strdup(buffer);
		nbytes = read(exec_list_node->hd_get_pipe[READ],
				buffer, BUFFER_SIZE - 1);
		count++;
	}
	close(exec_list_node->hd_get_pipe[READ]);
	waitpid(exec_list_node->hd_get_child, NULL, 0);
}

void	get_hd(t_msh *msh, t_exec_list *exec_list_node, int i)
{
	if (msh && exec_list_node)
	{
		if (pipe(exec_list_node->hd_get_pipe) < 0)
			errmsg_free_exit(msh, "pipe");
		exec_list_node->hd_get_child = fork();
		if (exec_list_node->hd_get_child < 0)
			errmsg_free_exit(msh, "fork");
		if (!(exec_list_node->hd_get_child))
			child_part(exec_list_node, i);
		else
			parent_part(msh, exec_list_node);
	}
}
