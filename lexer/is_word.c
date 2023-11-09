/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:03:23 by amennad           #+#    #+#             */
/*   Updated: 2023/11/09 15:22:18 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_world_end(char *prompt, int i)
{
	int	world_len;

	world_len = 0;
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != '\t'
		&& prompt[i] != '\0' && prompt[i] != '>' && prompt[i] != '<'
		&& prompt[i] != '>' && prompt[i] != '<'
		&& prompt[i] != '|' && prompt[i] != '$'
		&& prompt[i] != 34 && prompt[i] != 39)
	{
		world_len++;
		i++;
	}
	return (world_len);
}

int	is_word(t_msh *msh, char *prompt, int *i)
{
	int		world_len;
	char	*world;

	world_len = is_world_end(prompt, *i);
	world = ft_substr(prompt, *i, world_len);
	lexer_push(msh, world, WORD);
	free_chars(&world);
	*i += world_len - 1;
	return (0);
}
