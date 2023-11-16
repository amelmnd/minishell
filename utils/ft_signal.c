/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:28:00 by amennad           #+#    #+#             */
/*   Updated: 2023/11/16 11:29:00 by amennad          ###   ########.fr       */
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

void	ft_signal(t_msh *msh)
{
	if (msh->program_status == INTERACTIVE_STATUS)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		if (g_sigint == SIGINT)
		{
			msh->return_code = 130;
		}
		if (g_sigint == SIGQUIT)
		{
			msh->return_code = 0;
		}
	}
	if (msh->program_status == EXECUTION_STATUS)
		{
			signal(SIGINT, sig_handler);
			signal(SIGQUIT, sig_handler);
			if (g_sigint == SIGINT)
			{
				msh->return_code = 130;
			}
			if (g_sigint == SIGQUIT)
			{
				msh->return_code = 0;
			}
		}
}