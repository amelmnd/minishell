/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:24:25 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 20:14:31 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	ft_flag_n_cmp(char *s1)
{
	int	i;

	i = 0;
	if (s1[i] != '-')
		return (0);
	i++;
	while (s1[i])
	{
		if (s1[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	int		i;
	t_bool	n_flag;
	int		array_size;
	int		compare;

	(void)msh;
	i = 1;
	n_flag = FALSE;
	array_size = ft_array_size(exec_list_node->args_array);
	compare = ft_flag_n_cmp(exec_list_node->args_array[1]);
	if (compare)
		n_flag = TRUE;
	while (ft_flag_n_cmp(exec_list_node->args_array[i]))
		i++;
	while (exec_list_node->args_array[i])
	{
		printf("%s", exec_list_node->args_array[i]);
		if (i < array_size - 1)
			printf(" ");
		i++;
	}
	if (n_flag == FALSE)
		printf("\n");
}
*/

/*
L'option -n de la commande echo en shell supprime la nouvelle ligne à la fin de la sortie. 
En temps normal, echo ajoute automatiquement un retour à la ligne après avoir affiché le 
texte spécifié. Cependant, lorsque tu utilises l'option -n, cette nouvelle ligne n'est pas 
ajoutée. Voici un exemple pour illustrer son utilisation :

Sans -n :

sh
Copy code
echo "Bonjour"
echo "Monde"
Cela affichera :

Copy code
Bonjour
Monde
Avec -n :

sh
Copy code
echo -n "Bonjour"
echo " Monde"
Cela affichera :

Copy code
Bonjour Monde
Dans ce cas, "Monde" est affiché juste après "Bonjour" sur la même ligne.




User
Je viens de procéder aux essais suivants :
spardaspirit@spardaspirit-SATELLITE-PRO-R50-C:~/Desktop/minishell$ echo lol -n
lol -n
spardaspirit@spardaspirit-SATELLITE-PRO-R50-C:~/Desktop/minishell$ echo -n lol
lolspardaspirit@spardaspirit-SATELLITE-PRO-R50-C:~/Desktop/minishell$ ls exec -la
total 24
drwxrwxr-x  6 spardaspirit spardaspirit 4096 nov.  23 13:04 .
drwxrwxr-x 12 spardaspirit spardaspirit 4096 nov.  24 16:45 ..
drwxrwxr-x  2 spardaspirit spardaspirit 4096 nov.  24 16:10 build_exec_list
drwxrwxr-x  2 spardaspirit spardaspirit 4096 nov.  24 16:44 execution
drwxrwxr-x  2 spardaspirit spardaspirit 4096 nov.  24 16:10 here_doc
drwxrwxr-x  2 spardaspirit spardaspirit 4096 nov.  24 16:40 solo_builtin
spardaspirit@spardaspirit-SATELLITE-PRO-R50-C:~/Desktop/minishell$ 

C'était pour déterminer si la position d'une option importait. 
On dirait que pour echo oui, mais pas pour ls par exemple. Clarifie-moi ça

ChatGPT
La position des options dans une commande peut effectivement varier selon 
la commande utilisée.

Pour echo : L'option -n doit apparaître avant toute chaîne à afficher 
pour être prise en compte. Si elle apparaît après la chaîne, elle est 
traitée comme un texte ordinaire. Ainsi, echo -n "texte" supprime le retour 
à la ligne, tandis que echo "texte" -n affiche -n comme partie du texte.

Pour ls : Beaucoup de commandes Unix, comme ls, acceptent des options avant 
ou après les arguments non-optionnels (les noms de fichiers ou de répertoires, 
dans le cas de ls). Ces commandes utilisent souvent des bibliothèques d'analyse 
d'arguments standardisées qui gèrent les options de manière flexible.

Cette différence est liée à la façon dont chaque commande et ses options sont 
implémentées et analysées. Certaines commandes sont plus strictes sur la position 
des options que d'autres.

*/

void	echo_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	(void)msh;
	//print_exec_list_node(exec_list_node);
	
	if (exec_list_node->nb_words == 1)
		printf("\n");
	
}
