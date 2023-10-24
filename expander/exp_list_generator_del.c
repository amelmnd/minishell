#include "minishell.h"

void	exp_list_generator(t_msh *msh)
{
	int nb_pipe = 0;
	int i = -1;
	int nb_elt;
	int j;
	t_exp_list	*node = NULL;
	char *str = NULL;
	int exp_type = 0;

	while (nb_pipe <= 2 || nb_pipe >= 7)
		nb_pipe = msh_random_0_99(msh)%8;
	while (++i < nb_pipe + 1)
	{
		nb_elt = 0;
		while (nb_elt <= 5 || nb_elt >= 10)
			nb_elt = msh_random_0_99(msh)%10;
		j = -1;
		while (++j < nb_elt)
		{
			node = new_exp_list_node();
			str = gen_random_str(msh);
			exp_type = msh_random_0_99(msh) % 5;
			feed_exp_list_node(node, str, exp_type);
			add_exp_list_node(msh, node);
		}
		if (i != nb_pipe)
			add_pipe_exp_list_node(msh);
	}
	fill_the_first_node(msh);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	*msh;
	//int		return_value;
	
	msh = new_msh();
	init_msh(msh);
	
	feed_msh_acavenvp(msh, ac, av, envp);

	print_paths_from_path(msh);

	/*
	init_node_exp_list(msh);
	exp_list_generator(msh);
	print_exp_list(msh);
	print_exp_list_one_line(msh);
	
	build_exec_list(msh);
	print_exec_list(msh);
	*/

	//execution(msh);

	/*
	while (waitpid(-1, &return_value, 0) != -1)
	;
	*/

	//free_msh(msh);
	return (0);
}
