#ifndef FN_DEV_H
# define FN_DEV_H

# include "minishell.h"

typedef struct timeval	t_timestamp;

void	print_exp_list(t_msh *msh);
void	print_exp_list_one_line(t_msh *msh);
void	print_exec_list(t_msh *msh);
char *gen_random_str(t_msh *msh);

int	msh_random_0_99(t_msh *msh);
int	msh_random_0_127(t_msh *msh);

void	add_exp_list_node(t_msh *msh, t_exp_list *node);
void	feed_exp_list_node(t_exp_list *exp_list, char *str, int exp_type);
void	add_pipe_exp_list_node(t_msh *msh);
void	init_node_exp_list(t_msh *msh);
t_exp_list	*new_exp_list_node(void);
void	fill_the_first_node(t_msh *msh);
void	print_node(t_exp_list *node);

t_msh *new_msh(void);
t_timestamp	*new_timestamp(void);
void	init_msh(t_msh *msh);
void	free_msh(t_msh *msh);

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

#endif