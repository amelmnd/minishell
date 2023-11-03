#include "minishell.h"

int	get_size_ntcharss(char **ntcharss)
{
	int	i;

	i = 0;
	while (ntcharss[i])
		i++;
	return (i);
}

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

void	get_path_from_envp(t_msh *msh)
{
	char	*temp;
	int		i;
	
	temp = NULL;
	i = 0;
	while (msh->exec->envp[i] && ft_strncmp(msh->exec->envp[i], "PATH=", 5))
		i++;
	if (!(msh->exec->envp[i]))
		msh->exec->path_defined = 0;
	else if (!ft_strncmp(msh->exec->envp[i], "PATH=", 5))
	{
		temp = ft_strdup(msh->exec->envp[i]);
		msh->exec->path_from_envp = ft_substr(temp, 5, ft_strlen(temp));
		msh->exec->path_defined = 1;
	}
	else
		msh->exec->path_defined = 0;
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
	if (msh->exec->path_from_envp)
		msh->exec->paths_from_path = ft_split(msh->exec->path_from_envp, ':');
	append_slash_to_paths(msh);
}

void	feed_msh_with_envp(t_msh *msh, char **envp)
{
	printf("feed_msh_acavenvp : Entrée\n");
	msh->exec->envp = ntcharss_copy(envp);
	if (envp)
	{
		get_path_from_envp(msh);
		get_paths_from_path(msh);
	}
}

// à virer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void	print_paths_from_path(t_msh *msh)
{
	char 	**path;
	int		i;

	path = msh->exec->paths_from_path;
	i = -1;
	while (path[++i])
		printf("%s\n", path[i]);
}
