#include "minishell.h"

//les fonctions de ce fichier servent encore (et serviront jusqu'au bout)
//il faudra donc renommer le fichier, ou déplacer les fonctions dans des fichiers définitifs

//à transférer vers utils
int	get_size_ntcharss(char **ntcharss)
{
	int	i;

	i = 0;
	while (ntcharss[i])
		i++;
	return (i);
}

//à transférer vers utils
char	**ntcharss_copy(char **ntcharss_to_copy)
{
	char	**copy;
	int		len_to_copy;

	if (!ntcharss_to_copy)
		return (NULL);
	len_to_copy = get_size_ntcharss(ntcharss_to_copy);
	copy = (char **)malloc(sizeof(char *) * (len_to_copy + 1));
	if (!copy)
		return (NULL);
	len_to_copy = -1;
	while (ntcharss_to_copy[++len_to_copy])
		copy[len_to_copy] = ft_strdup(ntcharss_to_copy[len_to_copy]);
	copy[len_to_copy] = NULL;
	return (copy);
}

void	get_path_from_mshenv(t_msh *msh)
{
	char	*temp;
	int		i;
	
	temp = NULL;
	i = 0;
	while (msh->msh_env[i] && ft_strncmp(msh->msh_env[i], "PATH=", 5))
		i++;
	if (!(msh->msh_env[i]))
		msh->exec->path_defined = FALSE;
	else if (!ft_strncmp(msh->msh_env[i], "PATH=", 5))
	{
		temp = ft_strdup(msh->msh_env[i]);
		msh->exec->path_from_mshenv = ft_substr(temp, 5, ft_strlen(temp));
		msh->exec->path_defined = TRUE;
	}
	else
		msh->exec->path_defined = FALSE;
	free(temp);
}

void	append_slash_to_paths(t_msh *msh)
{
	char	*unslashed_path;
	int		i;

	unslashed_path = NULL;
	i = -1;
	while (msh->exec->paths_from_path[++i])
	{
		unslashed_path = ft_strdup(msh->exec->paths_from_path[i]);
		free_chars(&(msh->exec->paths_from_path[i]));
		msh->exec->paths_from_path[i] = ft_strjoin(unslashed_path, "/");
		free_chars(&unslashed_path);
	}
}

void	get_paths_from_path(t_msh *msh)
{
	get_path_from_mshenv(msh); // récupérer l'env du minishell !!
	if (msh->exec->path_from_mshenv)
		msh->exec->paths_from_path = ft_split(msh->exec->path_from_mshenv,
			':');
	append_slash_to_paths(msh);
}

/*
//ancien
void	feed_msh_with_envp(t_msh *msh, char **envp)
{
	//dprintf(2, "feed_msh_acavenvp : Entrée\n");
	msh->exec->envp = ntcharss_copy(envp);
	if (envp)
	{
		get_path_from_envp(msh); // récupérer l'env du minishell !!
		get_paths_from_path(msh);
	}
}
*/



/*
//futur
void	feed_msh_with_envp(t_msh *msh, char **envp)
{
	(void)envp; // à supprimer du prototype dès que msh->msh_env fonctionne
	//dprintf(2, "feed_msh_acavenvp : Entrée\n");
	if (envp)
	{
		get_path_from_envp(msh); // récupérer l'env du minishell !!
		get_paths_from_path(msh);
	}
}
*/


// à virer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void	print_paths_from_path(t_msh *msh)
{
	char 	**path;
	int		i;

	path = msh->exec->paths_from_path;
	i = -1;
	while (path[++i])
		dprintf(2, "%s\n", path[i]);
}
