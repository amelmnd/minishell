/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:13:22 by nstoutze          #+#    #+#             */
/*   Updated: 2023/10/12 20:53:12 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_STRUCT_H
# define ALL_STRUCT_H

typedef enum e_bool				t_bool;
typedef enum e_lexer_type		t_lexer_type;
typedef struct s_lexer_list		t_lexer_list;
typedef enum e_expander_type	t_expander_type;
typedef struct s_expander_list	t_expander_list;
typedef struct s_redirect		t_redirect;
typedef struct s_exec_list		t_exec_list;

enum	e_bool
{
	TRUE = 1,
	FALSE = 0
};

enum	e_lexer_type
{
	PIPE,
	WORD,
	S_QUOTE,
	D_QUOTE,
	R_REDIRECT,
	HEREDOC,
	W_REDIRECT,
	W_APPEND_REDIRECT,
	BLANK,
	VARIABLE,
	RETURN_VALUE,
	SPECIAL_VAR
};

struct	s_lexer_list
{
	t_lexer_list	*previous;
	t_lexer_list	*next;
	e_lexer_type	lexer_type;
	char			*str;
};

enum	e_expander_type
{
	WORD,
	R_ORIGIN_REDIRECT
	LIMITER_HEREDOC,
	W_DEST_REDIRECT,
	WA_DEST_REDIRECT
};

struct	s_expander_list
{
	t_expander_list	*previous;
	t_expander_list	*next;
	t_expander_type	expander_type;
	char			*str;
	char			*env_name;
	char			*env_value;
};

struct	s_redirect
{
	t_expander_type	expander_type;
	char			*value;
};

struct	s_exec_list
{
	t_exec_list	*previous;
	t_exec_list	*next;
	t_redirect	*redirect_array;
	char		*cmd;
	char		**arg_array;
};

#endif