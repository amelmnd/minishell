/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:00 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 17:16:34 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	signal(sig, SIG_IGN);
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	signal(sig, sig_handler);
}

void	sig_handler_exec(int sig)
{
	signal(sig, SIG_IGN);
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	signal(sig, sig_handler);
}

void	kill_heredoc(int sig)
{
	signal(sig, SIG_IGN);
	kill(getpid(), SIGKILL);
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	signal(sig, sig_handler);
}

void	ft_signal(t_msh *msh)
{
	if (msh->program_status == INTERACTIVE_STATUS)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (msh->program_status == EXECUTION_STATUS)
	{
		signal(SIGINT, sig_handler_exec);
		signal(SIGQUIT, sig_handler_exec);
	}
	if (msh->program_status == HEREDOC_STATUS)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
