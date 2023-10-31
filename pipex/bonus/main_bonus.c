/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:18:58 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/01 21:27:25 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_ppx	*ppx;
	int		return_value;

	ppx = NULL;
	return_value = 0;
	if (ac >= 5)
	{
		ppx = new_ppx();
		initialize_ppx(ppx);
		feed_ppx_with_acavenvp(ppx, ac, av, envp);
		pipex_bonus(ppx);
		while (waitpid(-1, &return_value, 0) != -1)
			;
		if (ppx)
			free_ppx(ppx);
	}
	else
		invalid_number_of_argument_msg_bonus();
	return (return_value);
}

/*
	system("lsof -c pipex_bonus");
	system("leaks pipex_bonus");
*/