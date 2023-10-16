/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:49:53 by amennad           #+#    #+#             */
/*   Updated: 2023/10/16 19:29:31 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

void			lexer_check(t_lexer_list *lexer_list, char *prompt);
t_bool			prompt_isempty(char **prompt);
t_lexer_list	*ft_push(t_lexer_list *list, char *item, t_lexer_type type);
int				lexex_create_list(t_lexer_list *lexer_list, char *prompt);

#endif
