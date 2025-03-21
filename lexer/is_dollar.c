/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:35:44 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 18:11:20 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_end(char *prompt, int i)
{
	int	var_len;

	var_len = 0;
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != '\t'
		&& prompt[i] != '\0' && prompt[i] != '>' && prompt[i] != '<'
		&& prompt[i] != '|' && prompt[i] != '"' && prompt[i] != 39
		&& prompt[i] != '$')
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
	free_chars(&var_name);
	*i += 1;
}

void	var_name_isalpha(t_msh *msh, char *prompt, int *i)
{
	int		var_len;
	char	*var_name;

	var_len = is_var_end(prompt, *i + 1);
	var_name = ft_substr(prompt, *i, var_len);
	lexer_push(msh, var_name, VARIABLE);
	free_chars(&var_name);
	*i += var_len - 1;
}

void	var_name_not_isalpha(t_msh *msh, char *prompt, int *i)
{
	char	*var_name;

	var_name = ft_substr(prompt, *i, 2);
	lexer_push(msh, var_name, SPECIAL_VAR);
	free_chars(&var_name);
	*i += 1;
}

int	is_dollar(t_msh *msh, char *prompt, int *i)
{
	char	*tmp_str;

	if (prompt[*i + 1] == '?')
		var_name_is_return_value(msh, prompt, i);
	else if (prompt[*i + 1] == 34 || prompt[*i + 1] == 39
		|| prompt[*i + 1] == '\0' || ((prompt[*i - 1] == ' '
				|| prompt[*i - 1] == '\t') && (prompt[*i + 1] == ' '
				|| prompt[*i + 1] == '\t' || prompt[*i + 1] == '\0'))
		|| (!ft_isalpha(prompt[*i + 1]) && (prompt[*i + 1] == '>'
				|| prompt[*i + 1] == '<' || prompt[*i + 1] == '|')))
	{
		tmp_str = ft_strdup("$");
		lexer_push(msh, tmp_str, WORD);
		free_chars(&tmp_str);
	}
	else if (ft_isalpha(prompt[*i + 1]) || (!ft_isalpha(prompt[*i + 1])
			&& prompt[*i + 1] == '_'))
		var_name_isalpha(msh, prompt, i);
	else if (!ft_isalpha(prompt[*i + 1]) && prompt[*i + 1] != 60
		&& prompt[*i + 1] != 62 && prompt[*i + 1] != '|' && prompt[*i + 1])
		var_name_not_isalpha(msh, prompt, i);
	return (msh->return_code);
}
