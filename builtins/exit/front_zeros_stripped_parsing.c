/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_zeros_stripped_parsing.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:33:48 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 16:02:24 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_len_fzs(t_msh *msh)
{
	char	*fzs;
	int		nb_signs;

	if (msh && msh->exit && msh->exit->front_zeros_stripped)
	{
		fzs = msh->exit->front_zeros_stripped;
		nb_signs = nb_signs_in_str(fzs);
		if ((nb_signs && msh->exit->len_fzs > 20)
			|| (!nb_signs && msh->exit->len_fzs > 19))
			non_numeric_arg_assignation(msh);
	}
}

static int	get_index_first_non_zero_chr(char *arg)
{
	int	i;

	i = -1;
	if (arg)
	{
		while (arg[++i] && arg[i] == '0')
			;
		return (i);
	}
	return (0);
}

static char	*get_front_zeros_stripped(t_msh *msh)
{
	char	*htss;
	int		index_first_non_zero_chr;

	if (msh && msh->exit)
	{
		htss = msh->exit->ht_spaces_stripped;
		index_first_non_zero_chr = get_index_first_non_zero_chr(htss);
		return (ft_substr(htss,
				index_first_non_zero_chr, msh->exit->len_htss));
	}
	return (NULL);
}

static void	full_of_zeros(t_msh *msh)
{
	char	*htss;
	int		i;

	if (msh && msh->exit)
	{
		htss = msh->exit->ht_spaces_stripped;
		i = -1;
		while (htss[++i])
		{
			if (!i && is_a_sign(htss[i]))
				continue ;
			if (htss[i] != '0')
				break ;
		}
		if (!(htss[i]))
		{
			msh->exit->ready = TRUE;
			msh->return_code = 0;
		}
	}
}

void	front_zeros_stripped_parsing(t_msh *msh)
{
	if (msh && msh->exit)
	{
		if (msh->exit->tests_ok)
			full_of_zeros(msh);
		if (msh->exit->tests_ok && !(msh->exit->ready))
		{
			msh->exit->front_zeros_stripped = get_front_zeros_stripped(msh);
			msh->exit->len_fzs = ft_strlen(msh->exit->front_zeros_stripped);
		}
		if (msh->exit->tests_ok && !(msh->exit->ready))
			check_len_fzs(msh);
	}
}
