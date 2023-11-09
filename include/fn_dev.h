#ifndef FN_DEV_H
# define FN_DEV_H

# include "minishell.h"

void	print_exp_list_one_line(t_msh *msh);
void	print_exec_list(t_msh *msh);

void	print_node(t_exp_list *node);

void	free_chars(char **dust);
void	free_ntcharss(char ***dust);
void	free_envlist(t_msh *msh);

void	print_exec_list_node(t_exec_list *exec_list_node);
void	print_exec_list(t_msh *msh);

void	ft_pipe(t_msh *msh);
void	ft_fork(t_msh *msh);
void	ft_close(int fd);
void	ft_duptwo(int pretender, int to_replace);

int	ft_strcmp(char *s1, char *s2);

# define BUFFER_SIZE 3
char	*get_next_line(int fd);
size_t	gnl_strlen(char *s);
char	*gnl_strchr(char *s, int c);
char	*gnl_strdup(char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_substr(char *s, unsigned int start, size_t len);

void	print_hd_in_exec_list_node(t_exec_list *exec_list_node); //dev
void	print_all_hd_remaining(t_msh *msh); //dev

void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node, int j);

void	builtin_way(t_msh *msh, t_exec_list *exec_list_node);

void	check_cmd_path_n_exec(t_msh *msh, t_exec_list *exec_list_node);

t_exec	*new_exec(void);
void	execution(t_msh *msh, char **envp);
int	    get_size_ntcharss(char **ntcharss);
char	**ntcharss_copy(char **ntcharss_to_copy);
void	get_path_from_envp(t_msh *msh);
void	get_paths_from_path(t_msh *msh);
void	feed_msh_with_envp(t_msh *msh, char **envp);
void	print_paths_from_path(t_msh *msh);

void	print_charss(char **str_array);

#endif