/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:08:26 by amennad           #+#    #+#             */
/*   Updated: 2023/10/18 12:24:32 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "all_struct.h"
// TODO DELETE START
# include "for_dev.h"
// TODO DELETE END

# include "lexer.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// IMP : readline.h is last include to avoid errors
# include <readline/readline.h>

void	exit_new_line(void);
void	clean_msh(t_msh *msh);

// error
void	exit_synthax_error(t_msh *msh, char *str);

#endif
