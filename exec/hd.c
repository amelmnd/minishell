#include "minishell.h"

t_hd	*new_hd(void)
{
	t_hd	*new;

	new = NULL;
	new = (t_hd *)malloc(sizeof(t_hd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->str = NULL;
	return (new);
}

t_bool hd_strcmp(char *limiter, char *line)
{
	char	*limiter_with_nl;
	t_bool	return_value;

	limiter_with_nl = ft_strjoin(limiter, "\n");
	if (ft_strcmp(limiter_with_nl, line))
		return_value = TRUE;
	else
		return_value = FALSE;
	free(limiter_with_nl);
	return (return_value);
}

void	feed_append_new_hd_node(t_exec_list *exec_list_node, char *line)
{
	t_hd	*new_hd_node;
	t_hd	*last_hd_node;

	new_hd_node = new_hd();
	new_hd_node->str = ft_strdup(line);
	last_hd_node = exec_list_node->hd;
	while (last_hd_node->next)
		last_hd_node = last_hd_node->next;
	last_hd_node->next = new_hd_node;
}

void	write_the_proper_number(int n)
{
	if (n == 0)
		write(STDOUT_FILENO, "0", 1);
	else if (n == 1)
		write(STDOUT_FILENO, "1", 1);
	else if (n == 2)
		write(STDOUT_FILENO, "2", 1);
	else if (n == 3)
		write(STDOUT_FILENO, "3", 1);
	else if (n == 4)
		write(STDOUT_FILENO, "4", 1);
	else if (n == 5)
		write(STDOUT_FILENO, "5", 1);
	else if (n == 6)
		write(STDOUT_FILENO, "6", 1);
	else if (n == 7)
		write(STDOUT_FILENO, "7", 1);
	else if (n == 8)
		write(STDOUT_FILENO, "8", 1);
	else if (n == 9)
		write(STDOUT_FILENO, "9", 1);
	else if (n == 10)
		write(STDOUT_FILENO, "10", 2);
	else if (n == 11)
		write(STDOUT_FILENO, "11", 2);
	else if (n == 12)
		write(STDOUT_FILENO, "12", 2);
	else if (n == 13)
		write(STDOUT_FILENO, "13", 2);
	else if (n == 14)
		write(STDOUT_FILENO, "14", 2);
}

void	get_hd(t_exec_list *exec_list_node, int i)
{
	char	*line;
	int		j;

	line = NULL;
	j = 0;
	while (42)
	{
		write(STDOUT_FILENO, exec_list_node->redirect_array[i].str, ft_strlen(exec_list_node->redirect_array[i].str));
		write(STDOUT_FILENO, "(", 1);
		write_the_proper_number(ft_strlen(exec_list_node->redirect_array[i].str));
		write(STDOUT_FILENO, ")> ", 3);
		line = get_next_line(STDIN_FILENO);
		if (hd_strcmp(exec_list_node->redirect_array[i].str, line))
			break ;
		if (j)
			feed_append_new_hd_node(exec_list_node, line);
		else
			exec_list_node->hd->str = ft_strdup(line);
		free(line);
		j++;
	}
	free(line);
}

void	clear_hd(t_exec_list *exec_list_node)
{
	t_hd	*hd_node;
	t_hd	*hd_node_next;

	hd_node = exec_list_node->hd;
	hd_node_next = NULL;
	while (hd_node)
	{
		hd_node_next = hd_node->next;
		if (hd_node->str)
		{
			free(hd_node->str);
			hd_node->str = NULL;
		}
		free(hd_node);
		hd_node = hd_node_next;
	}
}

void	get_hd_in_exec_list_node(t_exec_list *exec_list_node)
{
	int	i;

	i = -1;
	while (++i < exec_list_node->nb_redirects)
	{
		if (exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
		{
			if (exec_list_node->hd->str)
			{
				clear_hd(exec_list_node);
				exec_list_node->hd = new_hd();
			}
			get_hd(exec_list_node, i);
		}
	}
}

t_bool	hd_in_exec_list_node(t_exec_list *exec_list_node)
{
	int		i;

	i = -1;
	while (++i < exec_list_node->nb_redirects)
	{
		if (exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
			return (TRUE);
	}
	return (FALSE);
}

void	get_all_hd_content(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	while (exec_list_node)
	{
		if (hd_in_exec_list_node(exec_list_node))
		{
			exec_list_node->hd = new_hd();
			exec_list_node->contains_hd = TRUE;
			get_hd_in_exec_list_node(exec_list_node);
		}
		exec_list_node = exec_list_node->next;
	}
}

void	print_hd_in_exec_list_node(t_exec_list *exec_list_node)
{
	t_hd	*hd_node = exec_list_node->hd;

	while (hd_node)
	{
		printf("hd_node->str = %s", hd_node->str);
		hd_node = hd_node->next;
	}
}

void	print_all_hd_remaining(t_msh *msh)
{
	t_exec_list	*exec_list_node = msh->exec_list;

	while (exec_list_node)
	{
		print_hd_in_exec_list_node(exec_list_node);
		printf("\n== Passage à l'exec_list_node suivant (ce printf contient une nl au début) ==\n");
		exec_list_node = exec_list_node->next;
	}
}

void	write_hd_in_the_pipe(t_exec_list *exec_list_node)
{
	printf("write_hd_in_the_pipe : Entrée\n");
	t_hd	*hd_node;

	hd_node = exec_list_node->hd;
	while (hd_node)
	{
		printf("write_hd_in_the_pipe(while) : début itération\n");
		if (!(hd_node->str))
		{
			printf("write_hd_in_the_pipe(while) : entrée dans le if\n");
			write(exec_list_node->hd_pipe[WRITE], "\n", 1);
		}
		else
		{
			printf("write_hd_in_the_pipe(while) : entrée dans le else\n");
			write(exec_list_node->hd_pipe[WRITE],
				hd_node->str, ft_strlen(hd_node->str));
		}
		hd_node = hd_node->next;
		printf("write_hd_in_the_pipe(while) : début itération\n");
	}
	printf("write_hd_in_the_pipe : Sortie\n");
}

void	send_hd_through_pipe(t_exec_list *exec_list_node, int j)
{
	(void)j;
	if (exec_list_node->contains_hd)
	{	
		write_hd_in_the_pipe(exec_list_node);
		close(exec_list_node->hd_pipe[READ]);
		close(exec_list_node->hd_pipe[WRITE]);
	}
	exec_list_node = exec_list_node->next;
}

void	mark_erased_hd(t_exec_list *exec_list_node)
{
	int	i;
	int	nb_hd;

	i = exec_list_node->nb_redirects;
	nb_hd = 0;
	while (--i >= 0)
	{
		if (exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
		{
			nb_hd++;
			if (nb_hd >= 2)
				exec_list_node->redirect_array[i].exp_type = HEREDOC_ERASED;
		}
	}
}

void	mark_all_erased_hd(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	while (exec_list_node)
	{
		mark_erased_hd(exec_list_node);
		exec_list_node = exec_list_node->next;
	}
}

void	create_pipes_for_hd(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	exec_list_node = msh->exec_list;
	while (exec_list_node)
	{
		if (exec_list_node->contains_hd)
		{
			printf("create_pipes_for_hd AVANT LE PIPE ; hd_pipe[READ] = %d ; hd_pipe[WRITE] = %d\n", exec_list_node->hd_pipe[READ], exec_list_node->hd_pipe[WRITE]);
			int ret = pipe(exec_list_node->hd_pipe);
			if (ret == -1)
			perror("pipe error");
			printf("create_pipes_for_hd APRES LE PIPE ; hd_pipe[READ] = %d ; hd_pipe[WRITE] = %d\n", exec_list_node->hd_pipe[READ], exec_list_node->hd_pipe[WRITE]);
		}
		exec_list_node = exec_list_node->next;
	}
}

void	retrieve_hd_through_hdpipe(t_exec_list *exec_list_node, int j)
{
	(void)j;
	close(exec_list_node->hd_pipe[WRITE]);
	int ret = dup2(exec_list_node->hd_pipe[READ], STDIN_FILENO);
	if (ret == -1)
		perror("dup2 error");
}