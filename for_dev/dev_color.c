/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:50:55 by amennad           #+#    #+#             */
/*   Updated: 2023/11/05 12:14:37 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blue(void)
{
	dprintf(2, "\033[1;34m");
}

void	cyan(void)
{
	dprintf(2, "\033[1;36m");
}

void	pink(void)
{
	dprintf(2, "\033[1;35m");
}

void	red(void)
{
	dprintf(2, "\033[1;31m");
}

void	yellow(void)
{
	dprintf(2, "\033[1;33m");
}

void	green(void)
{
	dprintf(2, "\033[1;32m");
}

void	reset(void)
{
	dprintf(2, "\033[0m");
}
