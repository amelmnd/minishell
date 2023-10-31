/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:27:29 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/22 11:29:39 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	icis(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (i);
}

static void	janitor(char **dust)
{
	if (*dust)
	{
		free(*dust);
		*dust = NULL;
	}
}

static char	*read_fd(t_ppx *ppx, char *proto, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		nb_read_bytes;
	int		i;

	i = -1;
	while (++i <= BUFFER_SIZE)
		buffer[i] = '\0';
	nb_read_bytes = 1;
	while (!ft_strchr(buffer, '\n') && nb_read_bytes)
	{
		nb_read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (nb_read_bytes == -1 || (!nb_read_bytes && !proto))
		{
			janitor(&proto);
			return (0);
		}
		buffer[nb_read_bytes] = '\0';
		if (proto)
			proto = gnl_strjoin(ppx, proto, buffer);
		else
			proto = ft_strdup(ppx, buffer);
	}
	return (proto);
}

static char	*gen_line(t_ppx *ppx, int fd, char *proto, char **tank)
{
	char	*line;

	line = read_fd(ppx, proto, fd);
	proto = ft_strdup(ppx, line);
	janitor(&line);
	if (proto && ft_strchr(proto, '\n'))
	{
		line = ft_substr(ppx, proto, 0, icis(proto, '\n') + 1);
		if (ft_strlen(line) != ft_strlen(proto))
		{
			*tank = ft_substr(ppx, proto, icis(proto, '\n') + 1,
					ft_strlen(proto));
			janitor(&proto);
			return (line);
		}
		else
		{
			janitor(&line);
			return (proto);
		}
	}
	else if (proto)
		return (proto);
	janitor(&proto);
	return (0);
}

char	*get_next_line(t_ppx *ppx, int fd)
{
	char		*line;
	char		*proto;
	static char	*tank = NULL;

	proto = NULL;
	if (!tank)
		return (gen_line(ppx, fd, proto, &tank));
	else
	{
		if (ft_strchr(tank, '\n'))
		{
			line = ft_substr(ppx, tank, 0, icis(tank, '\n') + 1);
			proto = ft_substr(ppx, tank, icis(tank, '\n') + 1, ft_strlen(tank));
			janitor(&tank);
			tank = ft_strdup(ppx, proto);
			janitor(&proto);
			return (line);
		}
		else
		{
			proto = ft_strdup(ppx, tank);
			janitor(&tank);
			return (gen_line(ppx, fd, proto, &tank));
		}
	}
}
