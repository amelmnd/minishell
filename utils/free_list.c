/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:09:30 by amennad           #+#    #+#             */
/*   Updated: 2023/11/15 01:44:31 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO add here other free list inside msh

void	free_lexer_list(t_msh *msh)
{
	t_lexer_list	*current;
	t_lexer_list	*next;

	if (msh->lexer_list)
	{
		current = msh->lexer_list;
		while (current != NULL)
		{
			next = current->next;
			free_chars(&(current->str));
			free_chars(&(current->var_name));
			free_chars(&(current->var_value));
			free(current);
			current = next;
		}
		msh->lexer_list = NULL;
	}
}

void	free_exp_list(t_msh *msh)
{
	t_exp_list	*current;
	t_exp_list	*next;

	if (msh->exp_list)
	{
		current = msh->exp_list;
		while (current != NULL)
		{
			next = current->next;
			//free_chars(&(current->str));
			free(current);
			current = next;
		}
		msh->exp_list = NULL;
		msh->exp_current_type = 0;
	}
}

void	free_exec(t_msh *msh)
{
	if (msh->exec)
	{
		free_chars(&(msh->exec->path_from_mshenv));
		free_ntcharss(&(msh->exec->paths_from_path));
		free_chars(&(msh->exec->cmd_path_ready));
		free_ints(&(msh->exec->pid_t_array));
		free(msh->exec);
		msh->exec = NULL;
	}
}

void	free_redirect_array(t_exec_list *exec_list_node)
{
	int	i;

	i = -1;
	if (exec_list_node->redirect_array)
	{
		while (++i < exec_list_node->nb_redirects)
			free_chars(&(exec_list_node->redirect_array->str));
		free(exec_list_node->redirect_array);
		exec_list_node->redirect_array = NULL;
	}
}

void	free_hd(t_exec_list *exec_list_node)
{
	t_hd	*current;
	t_hd	*next;

	if (exec_list_node->hd)
	{
		current = exec_list_node->hd;
		while (current)
		{
			next = current->next;
			free_chars(&(current->str));
			current = next;
		}
	}
}

void	free_exec_list(t_msh *msh)
{
	t_exec_list	*current;
	t_exec_list	*next;
	
	if (msh && msh->exec_list)
	{
		current = msh->exec_list;
		while (current)
		{
			next = current->next;
			free_redirect_array(current);
			free_chars(&(current->cmd));
			free_ntcharss(&(current->args_array));
			free_hd(current);
			free(current);
			current = next;
		}
		msh->exec_list = NULL;
	}
}

// clean entre deux itérations de generate_prompt (donc msh et msh->msh_env ne sont pas free ici)
// msh, msh->msh_env et msh->env_list doivent être free lors d'une sortie du programme 
//via un signal
void	clean_msh_list(t_msh *msh)
{
	free_lexer_list(msh);
	free_exp_list(msh);
	free_exec_list(msh);
	free_exec(msh);
	free_ntcharss(&(msh->msh_env));
	//free_chars(&(msh->prompt));
}

void	free_envlist(t_msh *msh)
{
	t_env_list	*current;
	t_env_list	*next;

	if (msh->env_list)
	{
		current = msh->env_list;
		while (current)
		{
			next = current->next;
			free_chars(&(current->name));
			free_chars(&(current->value));
			free(current);
			current = NULL;
			current = next;
		}
	}
}
