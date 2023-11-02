/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/02 18:30:29 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_prompt(char *envp[])
{
	t_msh	*msh;
	char	*user;
	char	*prompt;

	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return ;
	env_list_generate(msh, envp);
	print_env_list(msh->env_list);
	user = getenv("USER");
	user = ft_strjoin(user, " $> ");
	while (1)
	{
		prompt = readline(user);
		lexer_check(msh, prompt);
		print_debug_lexer_list(msh->lexer_list, "main lexer_list");
		if (msh->return_code == 0 && msh->lexer_list)
			parser(msh);
		printf("msh->return_code = %d\n", msh->return_code);
		if (msh->return_code == 0 && msh->lexer_list)
        {
            expander(msh);
			/*
            if (msh->exp_list)
                print_debug_exp_list(msh->exp_list, "main expander_list");
			*/
        }
		clean_msh_list(msh);
	}
	
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	generate_prompt(envp);
	return (0);
}

/*
Observations expander :

//arrive lors de la première saisie de prompt, mais pas durant les suivantes
spardaspirit $> e'c'ho lol
str = c
Segmentation fault (core dumped)

// pareil, lors de la première saisie, mais pas durant les suivantes
spardaspirit $> lol lol
Segmentation fault (core dumped)

Hypothèse : s'il y a plus de deux mots dans le premier prompt : segfault


// un seul chevron ouvert provoque une segfault, même après plusieurs saisies d'autres prompts précédents
spardaspirit $> <

______ main lexer_list ______
str -> [<]
type -> R_REDIRECT

***********
bash: syntax error near unexpected token 'newline'
Segmentation fault (core dumped)


//même problème ici
spardaspirit $> <<

______ main lexer_list ______
str -> [<<]
type -> HEREDOC

***********
bash: syntax error near unexpected token 'newline'
Segmentation fault (core dumped)

// tous les chevrons provoquent le même type d'erreur menant à une segfault


spardaspirit $> lol

______ main lexer_list ______
str -> [lol]
type -> WORD

***********

______ main expander_list ______
str -> [lol]
type -> WORD_EXPANDED
***********
spardaspirit $> > lol

______ main lexer_list ______
str -> [>]
type -> W_REDIRECT

str -> [ ]
type -> BLANK
Segmentation fault (core dumped)


Après de nombreux tests durant une même exécution (donc après plusieurs saisies successives de prompts), les chevrons tout seul fonctionnent


Je remarque aussi que l'expander ne s'affiche plus.
En regardant le main.c, je remarque que le parser et l'expander ne se déclenchent que selon la valeur d'une variable dans msh qui ne semble pas initialisée.
La valeur de cette variable n'est ajustée que dans le lexer (lexer_create_list), et dans le parser. Elle n'est pas initialisée à la création de la structure msh.


spardaspirit $> cd lol $coucou 'cou'$lol <hou >>lol <d <j>l  (#) | allo 'cou$tata' "agrougrou$pouah$akiya"
str = cou
str = cou$tata

______ main lexer_list ______
str -> [cd]
type -> WORD

str -> [ ]
type -> BLANK

str -> [lol]
type -> WORD

str -> [ ]
type -> BLANK

str -> [$coucou]
type -> VARIABLE

str -> [ ]
type -> BLANK

str -> [cou]
type -> S_QUOTE

str -> [lol] 
type -> WORD //ne devrait pas plutôt être une variable ?

str -> [ ]
type -> BLANK

str -> [<]
type -> R_REDIRECT

str -> [hou]
type -> WORD

str -> [ ]
type -> BLANK

str -> [>>]
type -> W_APPEND_REDIRECT

str -> [lol]
type -> WORD

str -> [ ]
type -> BLANK

str -> [<]
type -> R_REDIRECT

str -> [d]
type -> WORD

str -> [ ]
type -> BLANK

str -> [<]
type -> R_REDIRECT

str -> [j]
type -> WORD

str -> [>]
type -> W_REDIRECT

str -> [l]
type -> WORD

str -> [ ]
type -> BLANK

str -> [(#)]
type -> WORD

str -> [ ]
type -> BLANK

str -> [|]
type -> PIPE

str -> [ ]
type -> BLANK

str -> [allo]
type -> WORD

str -> [ ]
type -> BLANK

str -> [cou$tata]
type -> S_QUOTE

str -> [agrougrou$pouah$akiya]
type -> D_QUOTE_VAR

***********
Segmentation fault (core dumped)

*/