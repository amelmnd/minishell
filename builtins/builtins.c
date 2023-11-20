/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:59:06 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/19 23:59:41 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Les builtins, lorsqu'ils ne sont pas exécutés dans le processus parent,
// assignent msh->return_code, lequel est est ensuite utilisé pour ajuster la
// valeur de l'exit, et ainsi, récupérer sa valeur à la fin de l'exec_loop (dans la
// fonction exec, lors du waitpid.)
//A noter que seule la commande du dernier exec_list_node assigne la valeur de
// msh->return_code !
void	builtin_way(t_msh *msh, t_exec_list *exec_list_node)
{
	t_bool	builtin;

	builtin = TRUE;
	if (msh && exec_list_node)
	{
		if (ft_strcmp(exec_list_node->cmd, "echo")
			|| ft_strcmp(exec_list_node->cmd, "/bin/echo"))
			echo_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "cd"))
			cd_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "pwd"))
			pwd_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "export"))
			export_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "unset"))
			unset_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "env")
			|| ft_strcmp(exec_list_node->cmd, "/bin/env"))
			env_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "exit"))
			exit_builtin(msh, exec_list_node);
		else
			builtin = FALSE;
		//L'exit_builtin contient un free de TOUT, ABSOLUMENT TOUT
		// si elle (la fonction) est appelée depuis un exec_list_node solo,
		// la mémoire du processus parent est libérée,
		// ce qui est indispensable pour éviter les leaks
		// Si elle est appelée depuis un processus enfant, la mémoire du processus enfant
		// sera libérée ; ce qui peut être bien, mais pas indispensable à ce qu'il parait
		// Procéder à la libération de TOUTE la mémoire allouée par ./minishell, que
		// ce soit dans le processus parent, ou un processus enfant, semble dans tous les cas
		// préférable
	}
	if (builtin)
		exit(msh->return_code);
}
