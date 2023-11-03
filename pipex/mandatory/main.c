/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:18:58 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/01 21:28:54 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
		invalid_number_of_argument_msg();
	else
		pipex(ac, av, envp);
	return (0);
}

/*
	system("lsof -c pipex_bonus");
	system("leaks pipex_bonus");	
*/