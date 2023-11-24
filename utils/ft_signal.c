/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:00 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 11:46:34 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sigint = 0;

void	sig_handler(int sig)
{
	g_sigint = sig;
	signal(sig, SIG_IGN);
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	signal(sig, sig_handler);
}

void    kill_heredoc(int sig)
{
		g_sigint = sig;
	signal(sig, SIG_IGN);
	kill(getpid(), SIGKILL);
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
	signal(sig, sig_handler);
}
// void    heredoc(int sig, siginfo_t *siginfo, void *context)
// {
// 	(void)siginfo;
// 	(void)context;
// 	(void)sig;
// }

void	ft_signal(t_msh *msh)
{
	if (msh->program_status == INTERACTIVE_STATUS)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (msh->program_status == EXECUTION_STATUS)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
	if (msh->program_status == HEREDOC_STATUS)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}