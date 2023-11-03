#ifndef FN_DEV_H
# define FN_DEV_H

# include "minishell.h"

typedef struct timeval	t_timestamp;

//void	print_exp_list(t_msh *msh);
void	print_exp_list_one_line(t_msh *msh);
void	print_exec_list(t_msh *msh);

void	print_node(t_exp_list *node);

t_msh *new_msh(void);
void	init_msh(t_msh *msh);
void	free_msh(t_msh *msh);

void	free_chars(char **dust);

void	build_exec_list(t_msh *msh);

void	print_exec_list_node(t_exec_list *exec_list_node);
void	print_exec_list(t_msh *msh);

t_exec_list *new_exec_list_node(void);
void	init_exec_list_node(t_exec_list *exec_list_node);
void	plug_exec_list_node(t_msh *msh, t_exec_list *exec_list_node);
void	create_and_plug_all_empty_exec_list_nodes(t_msh *msh);

void	get_nb_pipes_in_exp_list(t_msh *msh);
void	reset_counts(int *nb_w, int *nb_r);
void	feed_exec_list_node_data(t_msh *msh);
void	feed_last_exec_list_node_data(t_msh *msh);
void	feed_the_only_exec_list_node_data(t_msh *msh);

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

void	print_hd_in_exec_list_node(t_exec_list *exec_list_node);
void	mark_all_erased_hd(t_msh *msh);
void	send_hd_through_pipe(t_exec_list *exec_list_node, int i);
t_bool	hd_strcmp(char *limiter, char *line);
void	feed_append_new_hd_node(t_exec_list *exec_list_node, char *line);
void	get_hd(t_exec_list *exec_list_node, int i);
void	clear_hd(t_exec_list *exec_list_node);
void	get_hd_in_exec_list_node(t_exec_list *exec_list_node);
t_bool	hd_in_exec_list_node(t_exec_list *exec_list_node);
void	get_all_hd_content(t_msh *msh);
void	print_all_hd_remaining(t_msh *msh);

void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node, int j);

void	builtin_way(t_msh *msh, t_exec_list *exec_list_node);

void	check_cmd_path_n_exec(t_msh *msh, t_exec_list *exec_list_node);

void	retrieve_hd_through_hdpipe(t_exec_list *exec_list_node, int j);
void	create_pipes_for_hd(t_msh *msh);
t_exec	*new_exec(void);
t_hd	*new_hd(void);
void	execution(t_msh *msh, int ac, char **av, char **envp);
void	init_exec(t_msh *msh);
int	    get_size_ntcharss(char **ntcharss);
char	**ntcharss_copy(char **ntcharss_to_copy);
void	get_path_from_envp(t_msh *msh);
void	get_paths_from_path(t_msh *msh);
void	feed_msh_acavenvp(t_msh *msh, int ac, char **av, char **envp);
void	print_paths_from_path(t_msh *msh);

#endif