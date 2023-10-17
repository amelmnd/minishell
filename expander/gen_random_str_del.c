#include "../include/minishell.h"


char gen_random_printable_char_ascii(t_msh *msh)
{
	char	random_char = 0;

	while (!ft_isprint((int)random_char))
		random_char = (char)msh_random_0_127(msh);
	return (random_char);
}

char *gen_random_str(t_msh *msh)
{
	int len_str = 0;
	char *random_str;
	int i = -1;

	while (len_str < 1 || len_str > 15)
		len_str = msh_random_0_99(msh) % 15;
	random_str = (char *)malloc(sizeof(char) * (len_str + 1));
	if (!random_str)
		return (NULL);
	random_str[len_str] = '\0';
	while (++i < len_str)
		random_str[i] = gen_random_printable_char_ascii(msh);
	return (random_str);
}