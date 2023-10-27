/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expander_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:15:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/27 14:37:28 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_word(char *s1, char *s2)
{
	int		i;
	int		y;
	char	*result;

	i = 0;
	y = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
	{
		result = malloc(sizeof(char) * (ft_strlen(s1) + 1));
		if (!result)
			return (NULL);
	}
	if (!s1 && !s2)
	{
		result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (!result)
			return (NULL);
	}
	printf("S1 => %s\n", s1);
	printf("S2 => %s\n", s2);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			result[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[y] != '\0')
		{
			result[i + y] = s2[y];
			y++;
		}
	}
	result[i + y] = '\0';
	return (result);
}

void check_lexer_list(t_msh *msh ,t_lexer_list *tmp)
{
		char			*str;
		str = NULL;
		if (tmp && tmp->lexer_type == BLANK)
		{
			tmp = tmp->next;
			return ;
		}
		if (tmp && tmp->lexer_type == PIPE)
		{
			expander_push(msh, "|", PIPE_EXPANDED);
		}
		if (tmp && tmp->lexer_type > 0 && tmp->lexer_type < 4)
		{
			while (tmp && tmp->lexer_type > 0 && tmp->lexer_type < 4)
			{
				if (!str)
				{
					printf("ouin\n");
					printf("str => %s\n", str);
					printf("tmp->str => %s\n", tmp->str);
					str = ft_join_word(tmp->str, NULL);
				}
				else if (str)
				{
					printf("et ouin\n");
					str = ft_join_word(str, tmp->str);
				}
				printf("str => %s\n", str);
				tmp = tmp->next;
			}
			expander_push(msh, str, WORD_EXPANDED);
		}
}

void	create_expander_list(t_msh *msh)
{
	t_lexer_list	*tmp;


	tmp = msh->lexer_list;
	while (tmp->next)
	{
			check_lexer_list(msh, tmp);
			tmp = tmp->next;
	}
	// if (tmp->str)
	// {
	// 	printf("END tmp->str => %s\n", tmp->str);
	// 	if (tmp && tmp->lexer_type == BLANK)
	// 	{
	// 		return ;
	// 	}
	// 	if (tmp && tmp->lexer_type > 0 && tmp->lexer_type < 4)
	// 	{
	// 		str = ft_join_word(tmp->str, NULL);
	// 		expander_push(msh, str, WORD_EXPANDED);
	// 	}
	// }
	// check_lexer_type(msh, tmp);//
	print_debug_exp_list(msh->exp_list, "exp list");
}
