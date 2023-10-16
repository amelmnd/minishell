#ifndef FN_DEV_H
# define FN_DEV_H

# include "minishell.h"

typedef struct timeval	t_timestamp;

void	print_exp_list(t_msh *msh);
char *gen_random_str(t_msh *msh);

int	msh_random_0_99(t_msh *msh);
int	msh_random_0_127(t_msh *msh);

void	add_exp_list_node(t_msh *msh, t_exp_list *node);
void	feed_exp_list_node(t_exp_list *exp_list, char *str, int exp_type);
void	add_pipe_exp_list_node(t_msh *msh);
void	init_node_exp_list(t_msh *msh);
t_exp_list	*new_exp_list_node(void);

t_msh *new_msh(void);
t_timestamp	*new_timestamp(void);
void	init_msh(t_msh *msh);
void	free_msh(t_msh *msh);

#endif