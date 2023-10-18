/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:35:44 by amennad           #+#    #+#             */
/*   Updated: 2023/10/18 19:10:06 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_end(char *prompt, int i)
{
	int	var_len;

	var_len = 0;
	while (prompt[i] && (prompt[++i] != ' '
	|| prompt[++i] != '\t' || prompt[++i] != '\0'
	|| prompt[++i] != '>' || prompt[++i] != '<'
	|| prompt[++i] != '|'))
		var_len++;
	return (var_len);
}

int	is_dollar(t_msh *msh, char *prompt, int *i)
{
	char	c_before;
	char	c_after;
	int		len_var;
	char	*var_name;

	c_before = prompt[*i - 1];
	c_after = prompt[*i + 1];

	if ((*i == 0 && (c_after == ' ' || c_after == '\t' || c_after == '\0')) || ft_isalnum(c_before))
	{
		//TODO creat error commande not found
		exit_synthax_error(msh, "COMMANDE NOT FOUND");
		return (258);
	}

	len_var = is_var_end(prompt, *i);
	var_name = ft_substr(prompt, *i, len_var);

	if (c_after == '?')
	{
		lexer_push(msh, var_name, RETURN_VALUE);
		*i += len_var;
	}
	else if ((c_before == ' ' || c_before == '\t')
		&& (c_after == ' ' || c_after == '\t'))
	{
		lexer_push(msh, "$", WORD);
		*i += 2;
	}
	else if (!ft_isalpha(c_after))
	{
		lexer_push(msh, var_name, SPECIAL_VAR);
		*i += len_var;
	}
	else if (ft_isalpha(c_after))
	{
		lexer_push(msh, var_name, VARIABLE);
		*i += len_var;
	}

	return (0);
}