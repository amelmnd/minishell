#include "minishell.h"

/*
// les deux fonctions ci-dessous doivent rester solidaires
static void	norminette_pleasing(t_exec_list *exec_list_node, t_bool *bool)
{
	if (exec_list_node)
	{
		if (exec_list_node->args_array)
			*bool = TRUE;
	}
	else
		*bool = FALSE;
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
				norminette_pleasing(exec_list_node, &bool);
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
	t_bool		return_value;

	return_value = FALSE;
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
			printf("minishell: %s: %s\n", origin, strerror(errno));
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
			printf("minishell: %s: %s\n", origin, strerror(errno));
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
			printf("minishell: %s: %s\n", origin, strerror(errno));
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
			else if (redirect[i].exp_type == AMBIGUOUS_REDIRECT)
				printf("minishell: %s: ambiguous redirect\n", redirect[i].str);
			//aucun exit dans ces redirections (car elles s'effectuent dans le parent)
		}
	}
}

void	do_nf_solo_builtin(t_msh *msh)
{
	if (msh && msh->exec_list && msh->exec_list->cmd)
	{
		if (ft_strcmp(msh->exec_list->cmd, "cd"))
			cd_builtin(msh, msh->exec_list);
		else if (ft_strcmp(msh->exec_list->cmd, "export")
			&& !(msh->exec_list->args_array))
			export_builtin(msh, msh->exec_list);
		else if (ft_strcmp(msh->exec_list->cmd, "unset"))
			unset_builtin(msh, msh->exec_list);
		else if (ft_strcmp(msh->exec_list->cmd, "exit"))
			exit_builtin(msh, msh->exec_list);
	}
}

void	builtin_solo_without_fork(t_msh *msh)
{
	do_all_redir_solo_builtin(msh);
	if (!(msh->return_code))
		do_nf_solo_builtin(msh);
}
*/
