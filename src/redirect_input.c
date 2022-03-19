/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:11:18 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/19 21:06:25 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(char *limiter, int fd_input)
{
	char	*line;

	line = ft_strtrim(readline("heredoc> "), " \t");
	while (ft_strncmp(line, limiter, ft_strlen(line)))
	{
		write(fd_input, line, ft_strlen(line));
		write(fd_input, "\n", 1);
		free(line);
		line = ft_strtrim(readline("heredoc> "), " \t");
	}
	free(line);
	free(limiter);
	return (1);
}

int	copy_file(char	*in_file, int fd_out)
{
	int		fd_in;
	char	*line;
	char	*trimmed;

	trimmed = ft_strtrim(in_file, " <");
	if (ft_strncmp(in_file, ".temp_input", ft_strlen(in_file)))
		free(in_file);
	fd_in = open(trimmed, O_RDONLY);
	if (fd_in < 0)
	{
		ft_error_file("minishell", "no such file or directory", trimmed, -1);
		return (-1);
	}
	line = get_next_line(fd_in);
	while (line)
	{
		write(fd_out, line, ft_strlen(line));
		write(fd_out, "\n", 1);
		free(line);
		line = get_next_line(fd_in);
	}
	close(fd_in);
	free(trimmed);
	return (1);
}

int	redirect_input(char	**cmd)
{
	char	**files;
	int		fd_input;
	int		flag;
	int		i;

	files = find_files(cmd, "<");
	flag = 0;
	fd_input = open(".temp_input", O_RDWR | O_TRUNC | O_CREAT, 0777);
	i = -1;
	while (files[++i])
	{
		if (files[i][1] == '<')
			flag = ft_heredoc(ft_strtrim(files[i] + 2, " "), fd_input);
		else
			flag = copy_file(files[i], fd_input);
		if (flag == -1)
			return (-1);
	}
	free(files);
	close(fd_input);
	return (flag);
}

void	just_copy(char **files)
{
	int		i;
	int		fd_out;
	char	*trimmed;

	i = -1;
	while (files[++i])
	{
		if (files[i][1] == '>')
			trimmed = ft_strtrim(files[i] + 2, " ");
		else
			trimmed = ft_strtrim(files[i] + 1, " ");
		if (files[i][1] == '>')
			fd_out = open(trimmed, O_WRONLY | O_APPEND);
		else
			fd_out = open(trimmed, O_WRONLY | O_TRUNC);
		copy_file(".temp_input", fd_out);
		close(fd_out);
		free(trimmed);
	}
	if (i == 0)
		copy_file(".temp_input", 1);
}
