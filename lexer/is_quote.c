/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:14:55 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 18:11:20 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_closed_quotes(char *prompt, int i, char quote_type, t_bool *as_var)
{
	int	quote_len;

	quote_len = 0;
	while (prompt[i] && prompt[++i] != quote_type)
	{
		if (prompt[i] == '$' && (ft_isalpha(prompt[i + 1])
				|| prompt[i + 1] == '_') && quote_type == 34)
			*as_var = TRUE;
		quote_len++;
	}
	if (i == ft_strlen(prompt) && prompt[ft_strlen(prompt)] != quote_type)
		quote_len = -1;
	return (quote_len);
}

int	is_simple_quote(t_msh *msh, char *prompt, int *i)
{
	int		quote_len;
	char	*str;

	quote_len = is_closed_quotes(prompt, *i, 39, NULL);
	if (quote_len == -1)
	{
		exit_synthax_error(msh, "'");
		return (2);
	}
	str = ft_substr(prompt, *i + 1, quote_len);
	*i = *i + quote_len + 1;
	lexer_push(msh, str, S_QUOTE);
	free_chars(&str);
	return (msh->return_code);
}

int	is_double_quote(t_msh *msh, char *prompt, int *i)
{
	int		quote_len;
	char	*str;
	t_bool	as_var;

	as_var = FALSE;
	quote_len = is_closed_quotes(prompt, *i, 34, &as_var);
	if (quote_len == -1)
	{
		exit_synthax_error(msh, "\"");
		return (2);
	}
	str = ft_substr(prompt, *i + 1, quote_len);
	*i = *i + quote_len + 1;
	if (as_var == TRUE)
		lexer_push(msh, str, D_QUOTE_VAR);
	else
		lexer_push(msh, str, D_QUOTE);
	free_chars(&str);
	return (msh->return_code);
}
