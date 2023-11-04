#include "minishell.h"

void	get_nb_pipes_in_exp_list(t_msh *msh)
{
	int	nb_pipes = 0;
	t_exp_list	*exp_list_node = msh->exp_list;

	while (exp_list_node)
	{
		if (exp_list_node->exp_type == PIPE_EXPANDED)
			nb_pipes++;
		exp_list_node = exp_list_node->next;
	}
	msh->exec_list->nb_pipes = nb_pipes;
}

void	reset_counts(int *nb_w, int *nb_r)
{
	*nb_w = 0;
	*nb_r = 0;
}

void	feed_exec_list_node_data(t_msh *msh)
{
	t_exp_list	*exp_list_node;
	t_exec_list	*exec_list_node;
	int			nb_w;
	int			nb_r;

	exp_list_node = msh->exp_list;
	exec_list_node = msh->exec_list;
	nb_w = 0;
	nb_r = 0;
	while (exp_list_node)
	{
		if (exp_list_node->exp_type == WORD_EXPANDED)
			nb_w++;
		else if (exp_list_node->exp_type != PIPE_EXPANDED)
			nb_r++;
		else
		{
			exec_list_node->nb_words = nb_w;
			exec_list_node->nb_redirects = nb_r;
			exec_list_node = exec_list_node->next;
			reset_counts(&nb_w, &nb_r);
		}
		exp_list_node = exp_list_node->next;
	}
}

void	feed_last_exec_list_node_data(t_msh *msh)
{
	t_exec_list	*last_exec_list_node;
	t_exp_list	*last_pipe_exp_list_node;

	last_exec_list_node = msh->exec_list;
	last_pipe_exp_list_node = msh->exp_list;
	while (last_exec_list_node->next)
		last_exec_list_node = last_exec_list_node->next;
	while (last_pipe_exp_list_node->next)
		last_pipe_exp_list_node = last_pipe_exp_list_node->next;
	
	while (last_pipe_exp_list_node->exp_type != PIPE_EXPANDED)
	{
		if (last_pipe_exp_list_node->exp_type == WORD_EXPANDED)
			last_exec_list_node->nb_words++;
		else
			last_exec_list_node->nb_redirects++;
		last_pipe_exp_list_node = last_pipe_exp_list_node->previous;
	}
}

void	feed_the_only_exec_list_node_data(t_msh *msh)
{
	t_exp_list	*exp_list_node_i;

	exp_list_node_i = msh->exp_list;
	while (exp_list_node_i)
	{
		if (exp_list_node_i->exp_type == WORD_EXPANDED)
			msh->exec_list->nb_words++;
		else
			msh->exec_list->nb_redirects++;
		exp_list_node_i = exp_list_node_i->next;
	}
}