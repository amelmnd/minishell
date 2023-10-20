#include "minishell.h"

void	print_exec_list_node(t_exec_list *exec_list_node)
{
	//exec_list_node->redirect_array = NULL;
	printf("exec_list_node->nb_redirects = %d\n", exec_list_node->nb_redirects);
	printf("exec_list_node->cmd = %s\n", exec_list_node->cmd);
	//exec_list_node->args_array = NULL;
	printf("exec_list_node->nb_words = %d\n", exec_list_node->nb_words);
	printf("exec_list_node->next_pipe = %d\n", exec_list_node->next_pipe);
	printf("exec_list_node->nb_pipes = %d\n", exec_list_node->nb_pipes);
}

void	print_exec_list(t_msh *msh)
{
	t_exec_list	*exec_list = msh->exec_list;

	while (exec_list)
	{
		printf("\n==NEW EXEC_LIST_NODE==\n");
		print_exec_list_node(exec_list);
		exec_list = exec_list->next;
		printf("==END OF NODE==\n");
	}
}