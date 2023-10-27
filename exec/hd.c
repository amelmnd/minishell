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

void	get_hd(t_exec_list *exec_list_node, int i)
{
	char	*line;
	int		j;

	line = NULL;
	j = 0;
	while (42)
	{
		write(STDOUT_FILENO, exec_list_node->redirect_array[i].str, ft_strlen(exec_list_node->redirect_array[i].str));
		write(STDOUT_FILENO, "> ", 2);
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

