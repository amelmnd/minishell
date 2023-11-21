/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:35:44 by amennad           #+#    #+#             */
/*   Updated: 2023/11/21 08:08:27 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_end(char *prompt, int i)
{
	int	var_len;

	var_len = 0;
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != '\t'
		&& prompt[i] != '\0' && prompt[i] != '>' && prompt[i] != '<'
		&& prompt[i] != '|' && prompt[i] != '"' && prompt[i] != 39 && prompt[i] != '$')
	{
		var_len++;
		i++;
	}
	return (var_len + 1);
}

void	var_name_is_return_value(t_msh *msh, char *prompt, int *i)
{
	char	*var_name;

	var_name = ft_substr(prompt, *i, 2);
	lexer_push(msh, var_name, RETURN_VALUE);
	*i += 1;
}

void	var_name_isalpha(t_msh *msh, char *prompt, int *i)
{
	int		var_len;
	char	*var_name;

	var_len = is_var_end(prompt, *i + 1);
	var_name = ft_substr(prompt, *i, var_len);
	lexer_push(msh, var_name, VARIABLE);
	*i += var_len - 1;
}

void	var_name_not_isalpha(t_msh *msh, char *prompt, int *i)
{
	char	*var_name;

	var_name = ft_substr(prompt, *i, 2);
	lexer_push(msh, var_name, SPECIAL_VAR);
	*i += 1;
}

int	is_dollar(t_msh *msh, char *prompt, int *i)
{
	if (prompt[*i + 1] == '?')
		var_name_is_return_value(msh, prompt, i);
	else if (prompt[*i + 1] == 34 || prompt[*i + 1] == 39
		|| prompt[*i + 1] == '\0' || ((prompt[*i - 1] == ' '
				|| prompt[*i - 1] == '\t') && (prompt[*i + 1] == ' '
				|| prompt[*i + 1] == '\t' || prompt[*i + 1] == '\0'))
		|| (!ft_isalpha(prompt[*i + 1]) && (prompt[*i + 1] == '>'
				|| prompt[*i + 1] == '<' || prompt[*i + 1] == '|')))
		lexer_push(msh, ft_strdup("$"), WORD);
	else if (ft_isalpha(prompt[*i + 1]) || (!ft_isalpha(prompt[*i + 1])
			&& prompt[*i + 1] == '_'))
		var_name_isalpha(msh, prompt, i);
	else if (!ft_isalpha(prompt[*i + 1]) && prompt[*i + 1] != 60
		&& prompt[*i + 1] != 62 && prompt[*i + 1] != '|' && prompt[*i + 1])
		var_name_not_isalpha(msh, prompt, i);
	return (0);
}
