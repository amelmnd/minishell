/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:23:21 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 17:49:28 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	append_node_hdcstring(t_ppx *ppx, t_hdc *node)
{
	t_hdc	*hdc;

	hdc = ppx->hdc;
	while (hdc->next)
		hdc = hdc->next;
	hdc->next = node;
	node->next = NULL;
}

static void	set_hd_node_zero(t_ppx *ppx)
{
	t_hdc	*node_zero;

	node_zero = (t_hdc *)malloc(sizeof(t_hdc));
	if (!node_zero)
		exit(EXIT_FAILURE);
	ppx->hdc = node_zero;
	ppx->hdc->s = NULL;
	ppx->hdc->next = NULL;
}

void	get_here_doc_content(t_ppx *ppx)
{
	char	*line;
	t_hdc	*node;

	line = NULL;
	node = NULL;
	ppx->here_doc = 1;
	set_hd_node_zero(ppx);
	ppx->delimiter = ft_strjoin(ppx, ppx->av[2], "\n");
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		line = get_next_line(ppx, STDIN_FILENO);
		if (ft_strcmp(line, ppx->delimiter))
			break ;
		node = (t_hdc *)malloc(sizeof(t_hdc));
		if (!node)
			exit(EXIT_FAILURE);
		node->s = ft_strdup(ppx, line);
		append_node_hdcstring(ppx, node);
		free_chars(&line);
	}
	free_chars(&line);
}
