/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:23:52 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/05 19:54:24 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	search_cmd_among_paths(t_ppx *ppx)
{
	char	*abs_path_cmd;
	int		access_value;

	if (!ppx->paths_from_path)
		nsfod_msg(ppx, ppx->num_cmd);
	abs_path_cmd = NULL;
	ppx->i = -1;
	access_value = 0;
	build_slash_and_cmd(ppx);
	while (ppx->paths_from_path[++(ppx->i)])
	{
		ppx->chars_temp = ft_strdup(ppx, ppx->paths_from_path[ppx->i]);
		abs_path_cmd = ft_strjoin(ppx, ppx->chars_temp, ppx->slash_and_cmd);
		free_chars(&(ppx->chars_temp));
		access_value = access(abs_path_cmd, X_OK);
		if (!access_value)
			break ;
		free_chars(&abs_path_cmd);
	}
	if (access_value == -1)
		cmd_not_found_msg(ppx);
	ppx->abs_path_cmd = abs_path_cmd;
	return (!access_value);
}

static char	*get_only_the_cmd(t_ppx *ppx, char *abs_path_to_cmd)
{
	char	**relics;
	int		ntcharss_size;
	char	*only_the_cmd;

	relics = ft_split(ppx, abs_path_to_cmd, '/');
	ntcharss_size = get_size_ntcharss(relics);
	only_the_cmd = ft_strdup(ppx, relics[ntcharss_size -1]);
	free_charss(&relics);
	return (only_the_cmd);
}

static int	check_cmd_ready_to_use(t_ppx *ppx)
{
	int		access_value;
	char	**pot_rtu_cmd_with_args;
	char	*pot_rtu_cmd_without_args;

	pot_rtu_cmd_with_args = ft_split(ppx, ppx->av[ppx->num_cmd], ' ');
	pot_rtu_cmd_without_args = ft_strdup(ppx, pot_rtu_cmd_with_args[0]);
	access_value = access(pot_rtu_cmd_without_args, X_OK);
	if (!access_value)
	{
		ppx->abs_path_cmd = ft_strdup(ppx, pot_rtu_cmd_without_args);
		ppx->args = ntcharss_copy(ppx, pot_rtu_cmd_with_args);
		free_chars(&(ppx->args[0]));
		ppx->args[0] = get_only_the_cmd(ppx, pot_rtu_cmd_without_args);
	}
	free_chars(&pot_rtu_cmd_without_args);
	free_charss(&pot_rtu_cmd_with_args);
	if (!access_value)
		return (1);
	return (0);
}

int	cmd_parsing(t_ppx *ppx)
{
	if (!ft_strlen(ppx->av[ppx->num_cmd]))
	{
		write(2, "bash: : command not found\n", 26);
		return (0);
	}
	if ((!(ppx->av[ppx->num_cmd])) || (s_full_blanks(ppx->av[ppx->num_cmd])))
	{
		cmd_not_found_msg(ppx);
		return (0);
	}
	if (!check_cmd_ready_to_use(ppx))
		return (search_cmd_among_paths(ppx));
	else
		return (1);
	return (0);
}
