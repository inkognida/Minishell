/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:11:18 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/25 16:18:32 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_heredoc(char *line, char *limiter)
{
	free(line);
	free(limiter);
}

int	ft_heredoc(char *limiter, int fd_input)
{
	char	*line;
	pid_t	heredoc;

	heredoc = fork();
	if (heredoc < 0)
		exit(1);
	else if (heredoc == 0)
	{
		signal(SIGINT, on_heredoc_sig);
		line = ft_strtrim_free(readline("heredoc> "), " \t");
		while (ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			write(fd_input, line, ft_strlen(line));
			write(fd_input, "\n", 1);
			if (line)
				free(line);
			line = ft_strtrim_free(readline("heredoc> "), " \t");
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			exit(0);
		free_heredoc(line, limiter);
	}
	else
		waitpid(-1, 0, 0);
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

int	just_copy(char **files, char **cmds)
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
	return (free_arrs(files, cmds, 1, 1));
}
