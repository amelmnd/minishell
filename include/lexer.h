/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:49:53 by amennad           #+#    #+#             */
/*   Updated: 2023/10/18 14:17:10 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_bool	prompt_isempty(char **prompt);
void	lexer_check(t_msh *msh, char *prompt);
int		lexer_create_list(t_msh *msh, char *prompt);

// LIST
int		lexer_list_is_empty(t_lexer_list *list);
void	lexer_first_node(t_lexer_list *node);
void	lexer_push_new_node(t_msh *msh, t_lexer_list	*new_node);
void	lexer_push(t_msh *msh, char *str, t_lexer_type type);

//check cara
int		is_blank(t_msh *msh, char *prompt, int *i);
int		is_pipe(t_msh *msh, char *prompt, int *i);
int		is_right_bracket(t_msh *msh, char *prompt, int *i);
int		is_left_bracket(t_msh *msh, char *prompt, int *i);

#endif
