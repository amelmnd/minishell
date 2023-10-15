#ifndef FN_DEV_H
# define FN_DEV_H

# include <sys/time.h>
# include "minishell.h"

typedef struct timeval	t_timestamp;

void	print_exp_list(t_msh *msh);
char *gen_random_str(t_msh *msh);

#endif