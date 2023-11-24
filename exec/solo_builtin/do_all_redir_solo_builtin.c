/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_redir_solo_builtin.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:40:37 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 20:34:22 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_read_redirect_solo_builtin(t_msh *msh, char *origin)
{
	if (msh && msh->exec_list && origin)
	{
		if (access(origin, R_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(origin, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			msh->return_code = 1;
		}
	}
}

static void	do_write_redirect_solo_builtin(t_msh *msh, char *dest)
{
	if (msh && msh->exec && msh->exec_list && dest)
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
			msh->return_code = 1;
		}
		else
			close(msh->exec->fd_write_redirect);
	}
}

static void	do_wapp_redirect_solo_builtin(t_msh *msh, char *dest)
{
	if (msh && msh->exec && msh->exec_list && dest)
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
			msh->return_code = 1;
		}
		else
			close(msh->exec->fd_write_redirect);
	}
}

//no exit in these redirections (they take place in the parent process)
void	do_all_redir_solo_builtin(t_msh *msh)
{
	int			i;
	t_redirect	*redirect;

	i = -1;
	if (msh && msh->exec_list && msh->exec_list->redir_array)
	{
		redirect = msh->exec_list->redir_array;
		while (++i < msh->exec_list->nb_redirects && !(msh->return_code))
		{
			if (redirect[i].exp_type == R_ORIGIN_REDIRECT)
				do_read_redirect_solo_builtin(msh, redirect[i].str);
			else if (redirect[i].exp_type == W_DEST_REDIRECT)
				do_write_redirect_solo_builtin(msh, redirect[i].str);
			else if (redirect[i].exp_type == WA_DEST_REDIRECT)
				do_wapp_redirect_solo_builtin(msh, redirect[i].str);
			else if (redirect[i].exp_type == AMBIGOUS_REDIRECT_EXP)
				ambiguous_redirect_errmsg(redirect[i].str);
		}
	}
}
