#include "minishell.h"

// dev !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//dev
void	print_hd_in_exec_list_node(t_exec_list *exec_list_node)
{
	dprintf(2, "print_hd_in_exec_list_node : Entrée\n");
	t_hd	*hd_node = exec_list_node->hd;

	while (hd_node)
	{
		dprintf(2, "hd_node->str = %s", hd_node->str);
		hd_node = hd_node->next;
	}
}

// dev
void	print_all_hd_remaining(t_msh *msh)
{
	t_exec_list	*exec_list_node = msh->exec_list;

	while (exec_list_node)
	{
		print_hd_in_exec_list_node(exec_list_node);
		dprintf(2, "\n== Passage à l'exec_list_node suivant (ce dprintf 2, contient une nl au début) ==\n");
		exec_list_node = exec_list_node->next;
	}
}

// dev
void	write_the_proper_number(int n)
{
	if (n == 0)
		write(STDOUT_FILENO, "0", 1);
	else if (n == 1)
		write(STDOUT_FILENO, "1", 1);
	else if (n == 2)
		write(STDOUT_FILENO, "2", 1);
	else if (n == 3)
		write(STDOUT_FILENO, "3", 1);
	else if (n == 4)
		write(STDOUT_FILENO, "4", 1);
	else if (n == 5)
		write(STDOUT_FILENO, "5", 1);
	else if (n == 6)
		write(STDOUT_FILENO, "6", 1);
	else if (n == 7)
		write(STDOUT_FILENO, "7", 1);
	else if (n == 8)
		write(STDOUT_FILENO, "8", 1);
	else if (n == 9)
		write(STDOUT_FILENO, "9", 1);
	else if (n == 10)
		write(STDOUT_FILENO, "10", 2);
	else if (n == 11)
		write(STDOUT_FILENO, "11", 2);
	else if (n == 12)
		write(STDOUT_FILENO, "12", 2);
	else if (n == 13)
		write(STDOUT_FILENO, "13", 2);
	else if (n == 14)
		write(STDOUT_FILENO, "14", 2);
}