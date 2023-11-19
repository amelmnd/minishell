/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:17:30 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/19 22:31:59 by nstoutze         ###   ########.fr       */
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

static void	parent_part(t_exec_list *exec_list_node)
{
	char	buffer[BUFFER_SIZE];
	int		nbytes;
	int		count;

	close(exec_list_node->hd_get_pipe[WRITE]);
	nbytes = read(exec_list_node->hd_get_pipe[READ], buffer, BUFFER_SIZE - 1);
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
		pipe(exec_list_node->hd_get_pipe);
		exec_list_node->hd_get_child = fork();
		if (!(exec_list_node->hd_get_child))
			child_part(exec_list_node, i);
		else
			parent_part(exec_list_node);
	}
}

/*

void	get_hd(t_msh *msh, t_exec_list *exec_list_node, int i)
{
	char	*line;

	if (msh && exec_list_node)
	{
		pipe(exec_list_node->hd_get_pipe);
		exec_list_node->hd_get_child = fork();
		if (!(exec_list_node->hd_get_child))
		{
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
				//dprintf(2, "get_hd(child) : line = %s\n", line);
				write(exec_list_node->hd_get_pipe[WRITE], line, ft_strlen(line));
				write(exec_list_node->hd_get_pipe[WRITE], "\n", 1);
				free_chars(&line);
			}
			close(exec_list_node->hd_get_pipe[WRITE]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(exec_list_node->hd_get_pipe[WRITE]);
			
			char	buffer[1024];
			int		nbytes;
			int		count = 0;

			nbytes = read(exec_list_node->hd_get_pipe[READ], buffer, 1023);
			while (nbytes > 0)
			{
				buffer[nbytes] = '\0';
				//dprintf(2, "get_hd (parent) : buffer = %s\n", buffer);
				if (count)
					feed_append_new_hd_node(exec_list_node, buffer);
				else
					exec_list_node->hd->str = ft_strdup(buffer);
				nbytes = read(exec_list_node->hd_get_pipe[READ], buffer, 1023);
				// régler le problème du stockage du heredoc ici
				count++;
			}
			close(exec_list_node->hd_get_pipe[READ]);
			waitpid(exec_list_node->hd_get_child, NULL, 0);
		}
	}
}

//peut-être qu'il n'y a plus besoin de cette version modifiée de strcmp
// vu que readline ne prend pas le \n final, comme le faisait get_next_line
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

void	get_hd(t_msh *msh, t_exec_list *exec_list_node, int i)
{
	//kill(0, SIGKILL);
	char	*line;
	int		j;

	//line = NULL;
	j = 0;
	if (exec_list_node && exec_list_node->redir_array
		&& exec_list_node->redir_array[i].str && exec_list_node->hd)
	{
		while (42)
		{
			write(STDOUT_FILENO, " > ", 2);
			msh->program_status = HEREDOC_STATUS;
			line = get_next_line(STDIN_FILENO);
			if (feof(stdin))
				printf("Fin du fichier (Ctrl+D) détectée.\n");
			else
				printf("Erreur de lecture.\n");
			msh->program_status = EXECUTION_STATUS;
			if (ft_strlen(line) == 0)
			{	
				
				//rl_on_new_line();
				//rl_replace_line("", 0);
				//printf("\n");
				//rl_redisplay();
				
				kill(0, SIGKILL);
				printf("vide\n");
				break ;
			}
			printf("sortie de la structure conditionnelle if/else\n");
			if (hd_strcmp(exec_list_node->redir_array[i].str, line))
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
	printf("get_hd : sortie\n");
}
*/