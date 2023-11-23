/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:08:26 by amennad           #+#    #+#             */
/*   Updated: 2023/11/23 17:35:58 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1024

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

// IMP : readline.h is last include to avoid errors
# include <readline/readline.h>
# include <readline/history.h>

# include "all_struct.h"
# include "builtins.h"
# include "executor.h"
# include "expander.h"
# include "lexer.h"
# include "libft/libft.h"
# include "parser.h"
# include "utils.h"

// TODO DELETE START
# include "fn_dev.h" // à supprimer à terme
# include "for_dev.h"
// TODO DELETE END

#endif
