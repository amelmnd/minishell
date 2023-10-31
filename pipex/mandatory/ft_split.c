/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:58:01 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:47:32 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	nb_words_in_str(const char *s, char c)
{
	int	nb;
	int	i;

	nb = 0;
	i = -1;
	if (!s[0])
		return (0);
	if (s[++i] != c)
		nb++;
	while (s[++i])
	{
		if (s[i] != c && s[i - 1] == c)
			nb++;
	}
	return (nb);
}

static char	*next_word(t_ppx *ppx, const char *s, int *ptr_i, char c)
{
	char	*word;
	int		len_word;

	len_word = 0;
	while (s[*ptr_i] == c)
		(*ptr_i)++;
	while (s[*ptr_i + len_word] && s[*ptr_i + len_word] != c)
		len_word++;
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		errormsg_free_exit(ppx, "malloc problem \n");
	word[len_word] = '\0';
	len_word = 0;
	while (s[*ptr_i] && s[*ptr_i] != c)
	{
		word[len_word] = s[*ptr_i];
		len_word++;
		(*ptr_i)++;
	}
	return (word);
}

int	len_char_starstar_from_split(char **char_starstar)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (char_starstar[++i])
		len++;
	return (len);
}

char	**ft_split(t_ppx *ppx, char const *s, char c)
{
	char	**split;
	int		nb_words;
	int		num_word;
	int		i;

	if (!s)
		return (NULL);
	nb_words = nb_words_in_str(s, c);
	num_word = -1;
	i = 0;
	split = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!(split))
		errormsg_free_exit(ppx, "bash");
	split[nb_words] = NULL;
	while (++num_word < nb_words)
		split[num_word] = next_word(ppx, s, &i, c);
	return (split);
}
