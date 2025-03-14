/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:39:34 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 05:08:29 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

void			expander(t_msh *msh);

// LIST
void			expander_first_node(t_exp_list *node);
int				expander_list_is_empty(t_exp_list *list);
void			expander_push_new_node(t_msh *msh, t_exp_list *new_node);
void			expander_push(t_msh *msh, char *str, t_exp_type type);

// FN
void			all_in_str(t_msh *msh, char *str_value);
void			check_var_value(t_msh *msh);
void			create_expander_list(t_msh *msh);
void			db_quote_var_trans(t_msh *msh, t_lexer_list *tmp,
					int *not_exist_var);
void			dq_var_exist(t_msh *msh, t_lexer_list *tmp);
char			*ft_join_word(char *s1, char *s2);
char			*ft_one_word(char *s1);
t_lexer_list	*generate_str(t_msh *msh, t_lexer_list *tmp);
void			is_return_value(t_msh *msh, t_lexer_list *tmp,
					int *not_exist_var);
int				check_word(t_msh *msh, t_lexer_list *tmp);
void			that_is_variable(t_msh *msh, t_lexer_list *tmp,
					int *not_exist_var);
void			the_end(t_msh *msh, t_lexer_list *tmp, int not_exist_var);
int				that_is_wold(t_msh *msh, t_lexer_list *tmp, int *not_exist_var);
void			is_special_var(t_msh *msh, t_lexer_list *tmp);
void			musical_chairs(t_msh *msh, char *start_str,
					t_lexer_list *tmp, char *end_str);
#endif
