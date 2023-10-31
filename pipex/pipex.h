/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:00:59 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/04 20:24:18 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0
# define WRITE 1

# define BUFFER_SIZE 3

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

typedef struct s_hdc
{
	char			*s;
	struct s_hdc	*next;
}	t_hdc;

typedef struct s_ppx
{
	int		i;
	int		ac;
	char	**av;
	char	**envp;
	int		pipefd[2];
	pid_t	child;
	int		fd_input;
	int		fd_output;
	int		fd_temp;
	int		num_cmd;
	char	*path_from_envp;
	int		path_defined;
	char	**paths_from_path;
	char	*chars_temp;
	char	*slash_and_cmd;
	char	*abs_path_cmd;
	char	**args;
	int		here_doc;
	char	*delimiter;
	int		fd_temp_duplicated;
	t_hdc	*hdc;
}	t_ppx;

void	pipex(int ac, char **av, char **envp);
void	pipex_bonus(t_ppx *ppx);
t_ppx	*new_ppx(void);
void	initialize_ppx(t_ppx *ppx);
void	set_redirect(t_ppx *ppx);
void	here_doc_mode(t_ppx *ppx);
int		cmd_parsing(t_ppx *ppx);
void	get_ac_av_envp_into_ppx(t_ppx *ppx, int ac, char **av, char **envp);
void	get_path_from_envp(t_ppx *ppx);
void	get_paths_from_path(t_ppx *ppx);
void	build_slash_and_cmd(t_ppx *ppx);
void	get_here_doc_content(t_ppx *ppx);
void	feed_ppx_with_acavenvp(t_ppx *ppx, int ac, char **av, char **envp);

int		ft_strlen(const char *s);
char	**ntcharss_copy(t_ppx *ppx, char **ntcharss_to_copy);
int		get_size_ntcharss(char **ntcharss);
char	*ft_strdup(t_ppx *ppx, const char *s);
char	**ft_split(t_ppx *ppx, char const *s, char c);
char	*ft_substr(t_ppx *ppx, char const *s, int start, int len);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int length);
char	*ft_strjoin(t_ppx *ppx, char *s1, char const *s2);
size_t	gnl_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*gnl_strdup(t_ppx *ppx, char *s);
char	*gnl_strjoin(t_ppx *ppx, char *s1, char *s2);
char	*gnl_substr(t_ppx *ppx, char *s, unsigned int start, size_t len);
char	*get_next_line(t_ppx *ppx, int fd);
int		s_full_blanks(char *s);

void	free_ppx(t_ppx *ppx);
void	free_chars(char **dust);
void	free_charss(char ***dust);
void	free_after_iteration(t_ppx *ppx);

void	errormsg_free_exit(t_ppx *ppx, char *errormsg);
void	permission_denied_msg(t_ppx *ppx, int n);
void	nsfod_msg(t_ppx *ppx, int num_cmd);
void	invalid_number_of_argument_msg(void);
void	invalid_number_of_argument_msg_bonus(void);
void	first_file_open_failure_msg(t_ppx *ppx);
void	last_file_open_failure_msg(t_ppx *ppx);
void	cmd_not_found_msg(t_ppx *ppx);

void	ft_close(t_ppx *ppx, int fd);
void	ft_duptwo(t_ppx *ppx, int pretender, int to_replace);
int		ft_dup(t_ppx *ppx, int to_dup);
void	ft_execve(t_ppx *ppx);
void	ft_fork(t_ppx *ppx);
void	ft_pipe(t_ppx *ppx);

#endif