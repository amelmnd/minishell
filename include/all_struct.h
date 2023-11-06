/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:13:22 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/06 22:06:48 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_STRUCT_H
# define ALL_STRUCT_H

# include "minishell.h"

typedef enum e_bool						t_bool;
typedef enum e_lexer_type				t_lexer_type;
typedef struct s_lexer_list				t_lexer_list;
typedef enum e_expander_type			t_exp_type;
typedef struct s_expander_list			t_exp_list;
typedef struct s_redirect				t_redirect;
typedef struct s_exec_list				t_exec_list;
typedef struct s_msh					t_msh;
typedef struct s_exec_list_node_data	t_exec_list_node_data;
typedef enum e_read_write				t_read_write;
typedef struct s_exec					t_exec;
typedef struct s_hd						t_hd;
typedef enum e_pos_ppl					t_pos_ppl;
typedef struct s_env_list				t_env_list;

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
	SPECIAL_VAR,
	R_REDIRECT,
	HEREDOC,
	W_REDIRECT,
	W_APPEND_REDIRECT,
	BLANK,
	VARIABLE,
	RETURN_VALUE,
	D_QUOTE_VAR
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
	PIPE_EXPANDED,
	HEREDOC_ERASED
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

enum	e_read_write
{
	READ,
	WRITE
};

struct s_hd
{
	char	*str;
	t_hd	*next;
};

enum	e_pos_ppl
{
	INIT_POS_PPL_VALUE,
	FIRST,
	MIDDLE,
	LAST,
	SOLO
};

struct	s_exec_list
{
	t_exec_list	*previous;
	t_exec_list	*next;
	t_redirect	*redirect_array;
	int			nb_redirects;
	char		*cmd;
	char		**args_array;
	int 		nb_words;
	int			next_pipe;
	int			nb_pipes;
	t_hd		*hd;
	int			hd_pipe[2];
	t_bool		contains_hd;
	t_pos_ppl	pos_ppl;
	t_bool		contains_write_redirect;
	t_bool		contains_read_redirect;
};

struct s_exec
{
	int						ac;
	char					**av;
	char					**envp;
	int						path_defined;
	char					*path_from_envp;
	char					**paths_from_path;
	pid_t					child;
	int						pipefd[2];
	int						fd_temp;
	int						fd_read_redirect;
	int						fd_write_redirect;
	char					*cmd_path_ready;
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
	t_env_list		*env_list;
	t_exp_type		exp_current_type;
	t_lexer_list	*lexer_list;
	t_exp_list		*exp_list;
	t_exec_list		*exec_list;
	t_exec			*exec;
};

#endif
