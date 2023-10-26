/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_dev.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:51:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/26 09:04:09 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOR_DEV_H
# define FOR_DEV_H

# include "minishell.h"

// COLOR
void	blue(void);
void	cyan(void);
void	pink(void);
void	red(void);
void	yellow(void);
void	green(void);
void	reset(void);

// FN
void	print_lexer_list(t_lexer_list *list);
void	print_lexer_type_one_line(int lexer_type);
void	print_debug_lexer_list(t_lexer_list *list, char *name);
void	print_exp_list(t_exp_list *list);
void	print_debug_exp_list(t_exp_list *list, char *name);
void	print_env_list(t_env_list *list);
void	print_debug_env_list(t_env_list *list, char *name);

#endif
