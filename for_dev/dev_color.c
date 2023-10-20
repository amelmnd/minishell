/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:50:55 by amennad           #+#    #+#             */
/*   Updated: 2023/10/17 09:54:42 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	blue(void)
{
	printf("\033[1;34m");
}

void	cyan(void)
{
	printf("\033[1;36m");
}

void	pink(void)
{
	printf("\033[1;35m");
}

void	red(void)
{
	printf("\033[1;31m");
}

void	yellow(void)
{
	printf("\033[1;33m");
}

void	green(void)
{
	printf("\033[1;32m");
}

void	reset(void)
{
	printf("\033[0m");
}
