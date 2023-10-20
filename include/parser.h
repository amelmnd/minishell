/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:54:12 by amennad           #+#    #+#             */
/*   Updated: 2023/10/20 15:32:57 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

void	parser(t_msh *msh);
int		limit_is_valid(t_msh *msh);
int		check_valid_next(t_msh *msh);

#endif
