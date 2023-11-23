#ifndef FN_DEV_H
# define FN_DEV_H

# include "minishell.h"

void	print_exp_list_one_line(t_msh *msh);
void	print_exec_list(t_msh *msh);
void	print_exec_list_node(t_exec_list *exec_list_node);
void	print_exec_list(t_msh *msh);
void	print_node(t_exp_list *node);
void	print_pid_t_array(t_msh *msh);
void	print_paths_from_path(t_msh *msh);
void	print_ntcharss(char **str_array);

//void	free_chars(char **dust);
void	free_ntcharss(char ***dust);
void	free_envlist(t_msh *msh);


void	ft_close(int fd);
void	ft_duptwo(int pretender, int to_replace);

int	ft_strcmp(char *s1, char *s2);

void	builtin_way(t_msh *msh, t_exec_list *exec_list_node);

void	check_cmd_path_n_exec(t_msh *msh, t_exec_list *exec_list_node);

void	execution(t_msh *msh);
void	get_paths_from_path(t_msh *msh);


#endif