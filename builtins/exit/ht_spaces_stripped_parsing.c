/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_spaces_stripped_parsing.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:27:26 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 11:05:44 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	only_one_sign_at_start(t_msh *msh)
{
	char	*htss;

	htss = msh->exit->ht_spaces_stripped;
	if (ft_strlen(htss) >= 1 && nb_signs_in_str(htss) >= 1
		&& !is_a_sign(htss[0]))
		non_numeric_arg_assignation(msh);
}

static void	only_one_sign_without_digits(t_msh *msh)
{
	char	*htss;
	int		i;
	int		count_digits;

	htss = msh->exit->ht_spaces_stripped;
	i = -1;
	count_digits = 0;
	while (htss[++i])
	{
		if (!i && is_a_sign(htss[i]))
			continue ;
		if (ft_isdigit(htss[i]))
			count_digits++;
	}
	if (!count_digits)
		non_numeric_arg_assignation(msh);
}

void	ht_spaces_stripped_parsing(t_msh *msh, char *arg)
{
	msh->exit->ht_spaces_stripped = get_htss(arg);
	if (msh->exit->tests_ok)
		contains_non_sign_or_num_chr(msh);
	if (msh->exit->tests_ok)
		more_than_one_sign(msh);
	if (msh->exit->tests_ok)
		only_one_sign_at_start(msh);
	if (msh->exit->tests_ok)
		only_one_sign_without_digits(msh);
}
