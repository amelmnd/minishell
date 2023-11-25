/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:53:09 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/25 17:21:38 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

//before_prompt_loop
void		build_user_for_prompt(t_msh *msh);
t_msh		*new_msh(void);
void		show_no_args_for_minishell_error_msg(void);

//environment_management
void		env_list_generate(t_msh *msh, char *envp[]);
void		feed_env_list_node(t_env_list *env_list_node, char *var_n_value);
char		*ft_getenv(t_msh *msh, char *env_var);
void		generate_msh_env(t_msh *msh);
int			get_index_first_equal(char *str);
int			get_size_env_list(t_msh *msh);
char		*msh_getenv(t_msh *msh, char *var_name);
t_env_list	*new_env_list(void);
void		split_env_value(char *env_var, char **name, char **value);

// error
void		ambiguous_redirect_errmsg(char *str);
void		exit_synthax_error(t_msh *msh, char *str);
void		exit_command_not_foud(char *str);
void		exit_no_file_directory(char *str);
void		is_a_directory_errmsg(char *path);
void		print_cmd_not_found_errormsg(char *cmdnf);

//free
void		clean_msh_list(t_msh *msh);
void		errmsg_free_exit(t_msh *msh, char *msg);
void		free_chars(char **dust);
void		free_exec(t_msh *msh);
void		free_exec_list(t_msh *msh);
void		free_exit(t_msh *msh);
void		free_exp_list(t_msh *msh);
void		free_ints(int **dust);
void		free_lexer_list(t_msh *msh);
void		free_msh(t_msh *msh);

//generic
int			ft_msh_strchr(const char *s, int c);
int			get_size_ntcharss(char **ntcharss);
int			is_chr_in_str(char *s, char c);
char		**malloc_full_null_charss(int size);
char		**ntcharss_copy(char **ntcharss_to_copy);
void		reset_counts(int *x, int *y);

//readline_management
void		exit_new_line(t_msh *msh);

// signal
void		ft_signal(t_msh *msh);

//void	free_chars(char **dust);
void		free_ntcharss(char ***dust);
void		free_envlist(t_msh *msh);
int			ft_strcmp(char *s1, char *s2);
void		builtin_way(t_msh *msh, t_exec_list *exec_list_node);
void		check_cmd_path_n_exec(t_msh *msh, t_exec_list *exec_list_node);
void		execution(t_msh *msh);
void		get_paths_from_path(t_msh *msh);

#endif
