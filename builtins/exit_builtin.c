/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:32:25 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/22 21:53:47 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	num_arg_required_errmsg(t_msh *msh, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	msh->return_code = 2;
}

t_bool	is_diff_than_sign_or_num(char c)
{
	if (ft_isdigit(c) || c == '+' || c == '-')
		return (FALSE);
	return (TRUE);
}

t_bool	contains_non_sign_or_num_chr(char *stripped_arg)
{
	int	len_stripped_arg;
	int	i;

	len_stripped_arg = ft_strlen(stripped_arg);
	i = -1;
	while (++i < len_stripped_arg)
	{
		if (is_diff_than_sign_or_num(stripped_arg[i]))
			return (TRUE);
	}
	return (FALSE);
}

t_bool	more_than_one_sign(char *stripped_arg)
{
	int	count_signs;
	int	len_stripped_arg;
	int	i;

	count_signs = 0;
	len_stripped_arg = ft_strlen(stripped_arg);
	i = -1;
	while (++i < len_stripped_arg && count_signs <= 1)
	{
		if (stripped_arg[i] == '+' || stripped_arg[i] == '-')
			count_signs++;
	}
	if (count_signs > 1)
		return (TRUE);
	return (FALSE);
}

t_bool	only_one_sign_at_start(char *stripped_arg)
{
	if (ft_strlen(stripped_arg) == 1
		&& (stripped_arg[0] == '+' || stripped_arg[0] == '-'))
		return (TRUE);
	return (FALSE);
}


t_bool	sign_in_the_middle(char *stripped_arg)
{
	int len_stripped_arg;
	int	i;

	len_stripped_arg = ft_strlen(stripped_arg);
	i = -1;
	while (++i < len_stripped_arg)
	{
		if (!i)
			continue ;
		if (stripped_arg[i] == '+' || stripped_arg[i] == '-')
			return (TRUE);
	}
	return (FALSE);
}

t_bool	twenty_numbers_without_sign(char *stripped_arg)
{
	int	len_stripped_arg;
	int	i;
	int	count_signs;

	len_stripped_arg = ft_strlen(stripped_arg);
	i = -1;
	count_signs = 0;
	while (++i < len_stripped_arg)
	{
		if (stripped_arg[i] == '+' || stripped_arg[i] == '-')
			count_signs++;
	}
	if (len_stripped_arg == 20 && !count_signs)
		return (TRUE);
	return (FALSE);
}

t_bool	anomaly_in_arg(char *stripped_arg)
{
	return (contains_non_sign_or_num_chr(stripped_arg)
		|| more_than_one_sign(stripped_arg)
		|| only_one_sign_at_start(stripped_arg)
		|| sign_in_the_middle(stripped_arg));
}

int	get_sign(char *arg)
{
	if (arg[0] == '-')
		return (-1);
	return (1);
}

//9223372036854775807
long long	modulo_for_neg(long long n)
{
	while (n < 0)
	{
		n += 256;
		if (n == 256)
			return (0);
		
		dprintf(2, "modulo_for_neg : fin itération ; n = %lld\n", n);
		sleep(1);
		
	}
	return (n);
}

int	normal_cases_exit_atoi(t_msh *msh, char *arg)
{
	int			len_arg;
	int			i;
	long long	ret;

	len_arg = ft_strlen(arg);
	i = -1;
	ret = 0;
	while (++i < len_arg)
	{
		ret *= 10;
		if (!i && (arg[i] == '+' || arg[i] == '-'))
			continue ;
		ret += arg[i] - 48;
		if (ret < 0 || (i < len_arg && ret >= 922337203685477580
			&& arg[i + 1] >= '7'))
		{
			num_arg_required_errmsg(msh, arg);
			free_msh(msh);
			free_chars(&arg);
			exit(2);
		}
		dprintf(2, "normal_cases_exit_atoi(while) ; ret = %lld\n", ret);
	}
	if (ret < 0)
	{
		dprintf(2, "normal_cases_exit_atoi ; après le while ; ret = %lld\n", ret);
		while (ret < 0)
			ret -= 256;		
	}
	if (ret < 0)
		ret = modulo_for_neg(ret);
	ret *= get_sign(arg);
	//dprintf(2, "normal_cases_exit_atoi ; return imminent ; ret = %lld\n", ret);
	return ((int)(ret % 256));
}

// à ce stade, il n'y a pas plus d'un signe, et s'il y en a un, il est au début d'arg
/*
int	exit_atoi(t_msh *msh, char *arg)
{
	if (arg_stripped[0] == '0')
	{
		arg_first_zeros_stripped = strip_firsts_zeros(arg_stripped);
		free_chars(&arg_stripped);
		return (arg_first_zeros_stripped);
	}
	// une fois le zero_stripped construit, on vérifie la longueur de 20
	if (ft_strcmp(arg, "0") || ft_strcmp(arg, "+0") || ft_strcmp(arg, "-0")
		|| ft_strcmp(arg, "-9223372036854775808"))
		return (0);
	if (ft_strcmp(arg, "9223372036854775807"))
		return (255);
	if (ft_strcmp(arg, "-9223372036854775807"))
		return (1);
	return (normal_cases_exit_atoi(msh, arg));
}
*/

int	index_last_nschr(char *arg)
{
	int	i;

	i  = ft_strlen(arg);
	while (--i >= 0 && arg[i] == ' ')
		;
	return (i);
}

int	index_first_nschr(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] && arg[i] == ' ')
		;
	return (i);
}

int	get_size_arg_stripped(char *arg)
{
	////dprintf(2, "get_size_arg_stripped ; index_last_nschr(arg) = %d ; index_first_nschr(arg) = %d\n", index_last_nschr(arg), index_first_nschr(arg));
	return (index_last_nschr(arg) - index_first_nschr(arg) + 1);
}

int	get_index_first_non_zero_chr(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] && arg[i] == '0')
		;
	return (i);
}

char	*strip_firsts_zeros(char *arg_stripped)
{
	int		index_first_non_zero_chr;
	
	index_first_non_zero_chr = get_index_first_non_zero_chr(arg_stripped);
	return (ft_substr(arg_stripped,
			index_first_non_zero_chr, ft_strlen(arg_stripped)));
}

char	*ft_strip(char *arg)
{
	int		size_arg_stripped;
	char	*arg_stripped;
	int		index_first;

	size_arg_stripped = get_size_arg_stripped(arg);
	index_first = index_first_nschr(arg);
	arg_stripped = ft_substr(arg, index_first, size_arg_stripped);
	////dprintf(2, "ft_strip : return imminent ; arg_stripped(malloc) = %s\n", arg_stripped);
	return (arg_stripped);
}

// renvoie un booléen en fonction de si l'argument a été validé ou pas 
// assigne aussi msh->return_code
// n'exit pas ; la fonction principale s'en charge avec le return_code assigné
t_bool	valid_exit_arg(t_msh *msh, char *arg)
{
	char	*stripped_arg;
	t_bool	ret;
	
	if (ft_strlen(arg) == 1 && ft_isdigit(arg[0]))
	{
		msh->return_code = arg[0] - 48;
		return (TRUE);
	}
	stripped_arg = NULL;
	stripped_arg = ft_strip(arg);
	if (ft_strlen(stripped_arg) == 1 && ft_isdigit(stripped_arg[0]))
	{
		msh->return_code = (int)(stripped_arg[0] - 48);
		ret = TRUE;
	}
	else if (anomaly_in_arg(stripped_arg))
		ret = FALSE;
	else
	{
		msh->return_code = exit_atoi(msh, stripped_arg);
		ret = TRUE;
	}
	free_chars(&stripped_arg);
	return (ret);
}

t_bool	arg_full_of_spaces(char *arg)
{
	int	i;
	
	i = -1;
	while (arg[++i])
	{
		if (arg[i] != ' ')
			return (FALSE);
	}
	return (TRUE);
}

// renvoie un booléen en fonction de si l'argument a été validé ou pas 
// assigne aussi msh->return_code
// n'exit pas ; la fonction principale s'en charge avec le return_code assigné
t_bool	parsing_arg(t_msh *msh, char *arg)
{
	if (!ft_strlen(arg) || arg_full_of_spaces(arg))
		return (FALSE);
	return (valid_exit_arg(msh, arg));
}

static void	too_many_args_errmsg(t_msh *msh)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	msh->return_code = 1;
}

t_exit	*new_exit_struct(void)
{
	t_exit	*new;
	
	new = NULL;
	new = (t_exit *)malloc(sizeof(t_exit));
	if (!new)
		return (NULL);
	new->ht_spaces_stripped = NULL;
	new->front_zeros_stripped = NULL;
	new->tests_ok = TRUE;
	return (new);
}

void	exit_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	int	return_code;

	msh->exit = new_exit_struct();
	if (msh && exec_list_node)
	{
		if (exec_list_node->nb_words == 1)
			msh->return_code = 0;
		else if (exec_list_node->nb_words == 2)
		{
			if (!parsing_arg(msh, exec_list_node->args_array[1]))
				num_arg_required_errmsg(msh, exec_list_node->args_array[1]);
		}
		else if (exec_list_node->nb_words > 2)
		{
			if (parsing_arg(msh, exec_list_node->args_array[1]))
				too_many_args_errmsg(msh);
			else
				num_arg_required_errmsg(msh, exec_list_node->args_array[1]);
		}
		return_code = msh->return_code;
		free_msh(msh);
		exit(return_code);
	}
}

/*
Pas d'argument :
	assigne la valeur de retour à 0
	quitte le processus
Un seul argument :
	numérique, dans le range d'un long long, entouré d'espaces (avant et après, et ce grâce à des quotes) :
		assigne la valeur de retour au nombre%256
		quitte le processus
	numérique, hors du range d'un long long (min -9223372036854775808 ; max 9223372036854775807)
		affiche un message d'erreur : bash: exit: str_du_nb: numeric argument required
		assigne la valeur de retour à 2
		quitte le processus
	non numérique
		affiche un message d'erreur : bash: exit: arg : numeric argument required
		assigne la valeur de retour à 2
		quitte le processus
Plus d'un argument :
	Le premier est numérique dans le bon range long long
		affiche un message d'erreur : bash: exit: too many arguments
		assigne la valeur de retour à 1
		ne quitte pas le processus
	Le premier n'est pas numérique (des lettres, ou numérique hors du range long long)
		affiche un message d'erreur : bash: exit: arg : numeric argument required	
		assigne la valeur de retour à 2
		quitte le processus
*/

/*
On parcourt le tableau des arguments :
	Traitement du premier argument, sans quitter le processus
	Si premier argument valide, on passe au deuxième argument : 
		too many arguments (traitement en conséquence) + quitter le proc
*/


/*
cond_tests_ok

//assigne msh->return_code au passage
void EASY_TESTS(msh, arg)
	(cond_tests_ok)On vérifie si arg est full of spaces
	(cond_tests_ok)On vérifie si arg est de longueur nulle
	(cond_tests_ok)On vérifie si arg est de longueur 1 et que le seul chr est un nombre
		(sinon ça dégage instant)
		
//assigne msh->return_code au passage
void HT_SPACES_STRIPPED_PARSING(msh, arg)
	si msh->exit->tests_ok
		(malloc dans msh->ht_spaces_stripped) : On strip les spaces au début et à la fin
		On vérifie sur ce strip :
			(cond_tests_ok)la présence de chr non signe ou digit
			(cond_tests_ok)s'il y a plus d'un signe
			(cond_tests_ok)s'il n'y a qu'un seul signe, il doit être au début

//assigne msh->return_code au passage
void FRONT_ZEROS_STRIPPED_PARSING(msh)
	si msh->exit->tests_ok	
		(cond_tests_ok)on vérifie si le premier strip ne contient pas que des zéros
			(avec éventuellement un signe au début)
		(malloc dans msh->front_zeros_stripped) : On strip les éventuels zéros 
			entre le signe et le premier chiffre non nul			
		(cond_tests_ok) on vérifie si msh->front_zeros_stripped a une 
			longueur inférieure ou égale à 20

//assigne msh->return_code au passage
t_bool LIMITS_SINGLE_SHORTCUTS(msh)
	si msh->exit->tests_ok	
		if (ft_strcmp(msh->exit->front_zeros_stripped, "-9223372036854775808"))
		{
			msh->return_code =  0;
			return (TRUE);
		}
		if (ft_strcmp(msh->exit->front_zeros_stripped, "-9223372036854775807"))
		{
			msh->return_code =  1;
			return (TRUE);
		}
		if (ft_strcmp(msh->exit->front_zeros_stripped, "9223372036854775807"))
		{
			msh->return_code =  255;
			return (TRUE);
		}
	return (FALSE);

//assigne msh->return_code au passage
void	NORMAL_CASES_EXIT_ATOI(msh)
{
	int			i;
	long long	ret;
	char		*fzs;

	i = -1;
	ret = 0;
	fzs = msh->exit->front_zeros_stripped;
	while (++i < msh->exit->len_fzs)
	{
		ret *= 10;
		if (!i && (fzs[i] == '+' || fzs[i] == '-'))
			continue ;
		ret += fzs[i] - 48;
		if (ret < 0 || (i < len_fzs && ret >= 922337203685477580
			&& fzs[i + 1] > '7')) // à stocker dans une fonction annexe ?
		{
			msh->return_code = 2;
			return ;
		}
		dprintf(2, "normal_cases_exit_atoi(while) ; ret = %lld\n", ret);
	}
	if (ret < 0)
		ret = modulo_for_neg(ret);
	ret *= get_sign(arg);
	//dprintf(2, "normal_cases_exit_atoi ; return imminent ; ret = %lld\n", ret);
	return ((int)(ret % 256));
}


// POINT DE DEPART !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//assigne msh->return_code au passage
t_bool PARSING_ARG(msh, arg) :
	EASY_TESTS(msh, arg)
	HT_SPACES_STRIPPED_PARSING(msh, arg))
	FRONT_ZEROS_STRIPPED_PARSING(msh)
	if (!LIMITS_SINGLE_SHORTCUTS(msh) && msh->exit->tests_ok)
		NORMAL_CASES_EXIT_ATOI(msh)
	return (msh->exit->tests_ok)
*/