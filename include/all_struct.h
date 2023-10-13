/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:13:22 by nstoutze          #+#    #+#             */
/*   Updated: 2023/10/12 23:27:27 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_STRUCT_H
# define ALL_STRUCT_H

typedef enum e_bool				t_bool;
typedef enum e_lexer_type		t_lexer_type;
typedef struct s_lexer_list		t_lexer_list;
typedef enum e_exp_type			t_exp_type;
typedef struct s_exp_list		t_exp_list;
typedef struct s_redirect		t_redirect;
typedef struct s_exec_list		t_exec_list;
typedef struct s_msh			t_msh;

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
	t_lexer_type	lexer_type;
	char			*str;
	char			*var_name;
	char			*var_value;
};

enum	e_expander_type
{
	WORD_EXPANDED,
	R_ORIGIN_REDIRECT,
	LIMITER_HEREDOC,
	W_DEST_REDIRECT,
	WA_DEST_REDIRECT
};

struct	s_expander_list
{
	t_exp_list		*previous;
	t_exp_list		*next;
	t_exp_type		exp_type;
	char			*str;
};

struct	s_redirect
{
	t_exp_type		exp_type;
	char			*str;
};

struct	s_exec_list
{
	t_exec_list	*previous;
	t_exec_list	*next;
	t_redirect	*redirect_array;
	char		*cmd;
	char		**arg_array;
};

struct s_msh
{
	t_lexer_list		*lexer_list;
	t_exp_list		*exp_list;
	t_exec_list		*exec_list;
};

#endif
