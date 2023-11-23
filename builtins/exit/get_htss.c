/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_htss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:24:47 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 11:01:27 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	index_last_nschr(char *arg)
{
	int	i;

	i = ft_strlen(arg);
	while (--i >= 0 && arg[i] == ' ')
		;
	return (i);
}

static int	index_first_nschr(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] && arg[i] == ' ')
		;
	return (i);
}

static int	get_size_arg_stripped(char *arg)
{
	return (index_last_nschr(arg) - index_first_nschr(arg) + 1);
}

char	*get_htss(char *arg)
{
	int		size_arg_stripped;
	char	*arg_stripped;
	int		index_first;

	size_arg_stripped = get_size_arg_stripped(arg);
	index_first = index_first_nschr(arg);
	arg_stripped = ft_substr(arg, index_first, size_arg_stripped);
	return (arg_stripped);
}
