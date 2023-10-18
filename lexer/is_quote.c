/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:14:55 by amennad           #+#    #+#             */
/*   Updated: 2023/10/18 18:01:51 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_closed_quotes(char *prompt, int i, char quote_type)
{
	int	quote_len;

	quote_len = 0;
	while (prompt[i] && prompt[++i] != quote_type)
		quote_len++;
	if (i == ft_strlen(prompt) && prompt[ft_strlen(prompt)] != quote_type)
		quote_len = -1;
	return (quote_len);
}

int	is_simple_quote(t_msh *msh, char *prompt, int *i)
{
	int		quote_len;
	char	*str;

	quote_len = is_closed_quotes(prompt, *i, 39);
	if (quote_len == -1)
	{
		exit_synthax_error(msh, "'");
		return (258);
	}
	str = ft_substr(prompt, *i + 1, quote_len);
	*i = *i + quote_len + 1;
	lexer_push(msh, str, S_QUOTE);
	return (0);
}

int	is_double_quote(t_msh *msh, char *prompt, int *i)
{
	int		quote_len;
	char	*str;

	quote_len = is_closed_quotes(prompt, *i, '"');
	if (quote_len == -1)
	{
		exit_synthax_error(msh, "\"");
		return (258);
	}
	str = ft_substr(prompt, *i + 1, quote_len);
	*i = *i + quote_len + 1;
	lexer_push(msh, str, D_QUOTE);
	return (0);
}
