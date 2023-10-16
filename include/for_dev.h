/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_dev.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:51:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/16 15:09:38 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOR_DEV_H
# define FOR_DEV_H

# include "minishell.h"

void	print_list(t_lexer_list *list);
void	print_debug_list(t_lexer_list *list, char *name);

#endif

