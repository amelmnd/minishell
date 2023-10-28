/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:13:22 by nstoutze          #+#    #+#             */
/*   Updated: 2023/10/28 11:36:43 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_STRUCT_H
# define ALL_STRUCT_H

typedef enum e_bool				t_bool;
typedef enum e_lexer_type		t_lexer_type;
typedef struct s_lexer_list		t_lexer_list;
typedef enum e_expander_type	t_exp_type;
typedef struct s_expander_list	t_exp_list;
typedef struct s_redirect		t_redirect;
typedef struct s_exec_list		t_exec_list;
typedef struct s_env_list		t_env_list;
typedef struct s_msh			t_msh;

enum	e_bool
{
	TRUE = 1,
	FALSE = 0
};

enum	e_lexer_type
{
	PIPE, //0
	WORD, //1
	S_QUOTE, //2
	D_QUOTE, //3
	SPECIAL_VAR, //4
	R_REDIRECT, //5
	HEREDOC, //6
	W_REDIRECT, //7
	W_APPEND_REDIRECT, //8
	BLANK, //9
	VARIABLE, //10
	RETURN_VALUE, //11
	D_QUOTE_VAR //12
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
	WA_DEST_REDIRECT,
	PIPE_EXPANDED
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

struct	s_env_list
{
	t_env_list	*previous;
	t_env_list	*next;
	char		*name;
	char		*value;
};

struct s_msh
{
	int				return_code;
	t_lexer_list	*lexer_list;
	t_exp_list		*exp_list;
	t_exec_list		*exec_list;
	t_env_list		*env_list;
	t_exp_type		exp_current_type;
};

#endif
