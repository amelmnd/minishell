/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:17:30 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 18:24:23 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"

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
	if (exec_list_node && exec_list_node->redirect_array
		&& exec_list_node->redirect_array[i].str && exec_list_node->hd)
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
				/*
				rl_on_new_line();
				rl_replace_line("", 0);
				printf("\n");
				rl_redisplay();
				*/
				kill(0, SIGKILL);
				printf("vide\n");
				break ;
			}
			printf("sortie de la structure conditionnelle if/else\n");
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
	printf("get_hd : sortie\n");
}
