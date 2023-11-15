#include "minishell.h"

// les deux fonctions ci-dessous doivent rester solidaires
static void	norminette_pleasing(t_exec_list *exec_list_node, t_bool *bool)
{
	dprintf(2, "norminette_pleasing : Entrée\n");
	if (exec_list_node)
	{
		dprintf(2, "norminette_pleasing : entrée dans le if\n");
		if (get_size_ntcharss(exec_list_node->args_array) > 1)
		{
			dprintf(2, "norminette_pleasing : entrée dans le if interne\n");
			*bool = TRUE;
		}
		else
		{
			dprintf(2, "norminette_pleasing : entrée dans le else interne\n");
			*bool = FALSE;
		}
	}
	else
	{
		dprintf(2, "norminette_pleasing : entrée dans le else\n");
		*bool = FALSE;
	}
}

t_bool	is_cmd_in_nfsolobuiltin_list(t_exec_list *exec_list_node)
{
	char	*cmd;
	t_bool	bool;

	if (exec_list_node && exec_list_node->cmd)
	{
		cmd = ft_strdup(exec_list_node->cmd);
		if (ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "export")
			|| ft_strcmp(cmd, "unset") || ft_strcmp(cmd, "exit"))
		{
			if (ft_strcmp(cmd, "export"))
			{
				dprintf(2, "is_cmd_in_nfsolobuiltin_list : entrée dans le ft_strcmp specifique à export\n");
				norminette_pleasing(exec_list_node, &bool);
				if (bool == TRUE)
					dprintf(2, "is_cmd_in_nfsolobuiltin_list : bool après norminette pleasing : TRUE\n");
				else if (bool == FALSE)
					dprintf(2, "is_cmd_in_nfsolobuiltin_list : bool après norminette pleasing : FALSE\n");
			}
			else
				bool = TRUE;
		}
		else
			bool = FALSE;
	}
	else
		bool = FALSE;
	free_chars(&cmd);
	return (bool);
}

t_bool	no_fork_solo_builtin(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	if (msh && msh->exec_list)
	{
		exec_list_node = msh->exec_list;
		if (exec_list_node->pos_ppl != SOLO)
			return (FALSE);
		return (is_cmd_in_nfsolobuiltin_list(exec_list_node));
	}
	return (FALSE);
}

void	do_read_redirect_solo_builtin(t_msh *msh, char *origin)
{
	if (msh && msh->exec_list && origin)
	{
		if (access(origin, R_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(origin, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			msh->return_code = 1;
		}
	}
}

void	do_write_redirect_solo_builtin(t_msh *msh, char *dest)
{
	if (msh && msh->exec && msh->exec_list && dest)
	{
		msh->exec->fd_write_redirect = open(dest,
			O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (msh->exec->fd_write_redirect == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(dest, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			msh->return_code = 1;
		}
		else
			close(msh->exec->fd_write_redirect);
	}
}

void	do_wapp_redirect_solo_builtin(t_msh *msh, char *dest)
{
	if (msh && msh->exec && msh->exec_list && dest)
	{
		msh->exec->fd_write_redirect = open(dest,
			O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (msh->exec->fd_write_redirect == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(dest, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			msh->return_code = 1;
		}
		else
			close(msh->exec->fd_write_redirect);
	}
}

void	do_all_redir_solo_builtin(t_msh *msh)
{
	int	i;
	t_redirect	*redirect;

	i = -1;
	if (msh && msh->exec_list && msh->exec_list->redirect_array)
	{
		redirect = msh->exec_list->redirect_array;
		while (++i < msh->exec_list->nb_redirects && !(msh->return_code))
		{
			if (redirect[i].exp_type == R_ORIGIN_REDIRECT)
				do_read_redirect_solo_builtin(msh, redirect[i].str);
			else if (redirect[i].exp_type == W_DEST_REDIRECT)
				do_write_redirect_solo_builtin(msh, redirect[i].str);
			else if (redirect[i].exp_type == WA_DEST_REDIRECT)
				do_wapp_redirect_solo_builtin(msh, redirect[i].str);
			//else if (redirect[i].exp_type == AMBIGUOUS_REDIRECT)
			//	printf("minishell: %s: ambiguous redirect\n", redirect[i].str);
			// ce bloc sera activé quand l'expander assignera l'enum AMBIGUOUS_REDIRECT
			
			//aucun exit dans ces redirections (car elles s'effectuent dans le parent)
		}
	}
}

void	do_nf_solo_builtin(t_msh *msh)
{
	dprintf(2, "do_nf_solo_builtin ; Entrée\n");
	if (msh && msh->exec_list && msh->exec_list->cmd)
	{
		dprintf(2, "do_nf_solo_builtin ; entrée dans le if de sécurité\n");
		dprintf(2, "do_nf_solo_builtin(if sécu) ; msh->exec_list->cmd = %s\n", msh->exec_list->cmd);

		if (ft_strcmp(msh->exec_list->cmd, "cd"))
		{
			dprintf(2, "do_nf_solo_builtin : entrée 1\n");
			cd_builtin(msh, msh->exec_list);
		}
		else if (ft_strcmp(msh->exec_list->cmd, "export"))
		{
			dprintf(2, "do_nf_solo_builtin : entrée 2\n");
			export_builtin(msh, msh->exec_list);
		}
		else if (ft_strcmp(msh->exec_list->cmd, "unset"))
		{
			dprintf(2, "do_nf_solo_builtin : entrée 3\n");
			unset_builtin(msh, msh->exec_list);
		}
		else if (ft_strcmp(msh->exec_list->cmd, "exit"))
		{
			dprintf(2, "do_nf_solo_builtin : entrée 4\n");
			exit_builtin(msh, msh->exec_list);
		}
	}
	dprintf(2, "do_nf_solo_builtin ; Sortie\n");
}

void	builtin_solo_without_fork(t_msh *msh)
{
	do_all_redir_solo_builtin(msh);
	if (!(msh->return_code))
		do_nf_solo_builtin(msh);
}
