/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:43:06 by hardella          #+#    #+#             */
/*   Updated: 2022/03/18 22:19:26 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static	char	*free_null(char **line)
{
	free(*line);
	return (NULL);
}

static int	get_read(int fd, char *buff)
{
	if (ft_strlen_gnl(buff))
		return (ft_strlen_gnl(buff));
	else
		return (read(fd, buff, BUFFER_SIZE));
}

static char	*gnl_main(int fd, char *buff, char *line)
{
	int		r_b;
	char	*g_n;

	r_b = get_read(fd, buff);
	if (r_b <= 0)
		return (free_null(&line));
	while (r_b)
	{
		buff[r_b] = '\0';
		g_n = ft_strchr_gnl(buff, '\n');
		if (g_n)
		{
			*g_n = '\0';
			line = ft_strjoin_gnl(line, buff);
			ft_strlcpy_gnl(buff, ++g_n, BUFFER_SIZE);
			return (line);
		}
		line = ft_strjoin_gnl(line, buff);
		r_b = read(fd, buff, BUFFER_SIZE);
	}
	buff[0] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{	
	char		*line;
	static char	buff[BUFFER_SIZE + 1];

	line = (char *)malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_null(&line));
	line = gnl_main(fd, buff, line);
	return (line);
}
