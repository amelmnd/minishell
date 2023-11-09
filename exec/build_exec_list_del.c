#include "minishell.h"

void	build_exec_list(t_msh *msh)
{
	malloc_exec_list_nodes(msh);
	feed_exec_list_nodes_data(msh);
	malloc_exec_list_node_arrays(msh); //
	feed_exec_list_nodes_cmd(msh);
	assign_pos_ppl_exec_list(msh);
	feed_exec_list_node(msh);
	scan_redirects(msh);
}
