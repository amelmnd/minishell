/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:39:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/26 10:59:59 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

void	expander(t_msh *msh);

// LIST
int		expander_list_is_empty(t_exp_list *list);
void	expander_first_node(t_exp_list *node);
void	expander_push_new_node(t_msh *msh, t_exp_list	*new_node);
void	expander_push(t_msh *msh, char *str, t_exp_type type);

// FN
void	dq_var_exist(t_msh *msh, t_lexer_list *tmp);
void	check_var_value(t_msh *msh);

#endif
