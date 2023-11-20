/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:53:28 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/20 15:29:14 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_read_redir(t_msh *msh, char *origin)
{
	if (msh && msh->exec)
	{
		msh->exec->fd_read_redirect = open(origin, O_RDONLY);
		if (msh->exec->fd_read_redirect == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(origin, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		else
		{
			if (dup2(msh->exec->fd_read_redirect, STDIN_FILENO) < 0)
				errmsg_free_exit(msh, "dup2");
		}
	}
}

static void	do_write_redir(t_msh *msh, char *dest)
{
	if (msh && msh->exec)
	{
		msh->exec->fd_write_redirect = open(dest,
				O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (msh->exec->fd_write_redirect == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(dest, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		else
		{
			if (dup2(msh->exec->fd_write_redirect, STDOUT_FILENO) < 0)
				errmsg_free_exit(msh, "dup2");
		}
	}
}

static void	do_wapp_redir(t_msh *msh, char *dest)
{
	if (msh && msh->exec)
	{
		msh->exec->fd_write_redirect = open(dest,
				O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (msh->exec->fd_write_redirect == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(dest, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(1);
		}
		else
		{
			if (dup2(msh->exec->fd_write_redirect, STDOUT_FILENO) < 0)
				errmsg_free_exit(msh, "dup2");
		}
	}
}

void	do_redir(t_msh *msh, t_exec_list *exec_list_node, int i)
{
	t_redirect	redir_box;

	if (msh && exec_list_node && exec_list_node->redir_array)
	{
		redir_box = exec_list_node->redir_array[i];
		if (redir_box.exp_type == LIMITER_HEREDOC)
			retrieve_hd_through_hdpipe(exec_list_node);
		else if (redir_box.exp_type == R_ORIGIN_REDIRECT)
			do_read_redir(msh, redir_box.str);
		else if (redir_box.exp_type == W_DEST_REDIRECT)
			do_write_redir(msh, redir_box.str);
		else if (redir_box.exp_type == WA_DEST_REDIRECT)
			do_wapp_redir(msh, redir_box.str);
		/*
		else if (redir_box.exp_type == AMBIGUOUS_REDIRECT)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(redir_box.str, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("ambiguous redirect\n", 2);
			exit(1);
		}
		*/
	}
}
