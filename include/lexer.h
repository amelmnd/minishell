/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:49:53 by amennad           #+#    #+#             */
/*   Updated: 2023/10/13 14:49:58 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

void	lexer_check(t_lexer_list **lexer_list, char *prompt);
t_bool	prompt_isempty(char **prompt);

#endif
