/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:04:57 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/05 19:44:20 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	find_redirect_file(char *cmd, char redirect, int *start_len_i)
{
	start_len_i[2] = -1;
	while (cmd[++start_len_i[2]])
	{
		if (cmd[start_len_i[2]] == '\'')
			while (cmd[++start_len_i[2]] != '\'' && cmd[start_len_i[2]])
				continue ;
		if (cmd[start_len_i[2]] == '"')
		{
			while (cmd[++start_len_i[2]] != '"' && cmd[start_len_i[2]])
				continue ;
		}
		if (cmd[start_len_i[2]] == redirect)
		{
			start_len_i[0] = start_len_i[2];
			while (cmd[++start_len_i[2]] == ' ')
				continue ;
			while (cmd[start_len_i[2]] && cmd[start_len_i[2]] != ' ' && \
			cmd[start_len_i[2]] != '<' && cmd[start_len_i[2]] != '>')
				start_len_i[2]++;
			start_len_i[1] = start_len_i[2] - start_len_i[0];
			return (1);
		}
	}
	return (0);
}

int	copy_file(char	*in_file, int fd_out)
{
	int		fd_in;
	char	*line;
	char	*trimmed;

	trimmed = ft_strtrim(in_file, " <");
	free(in_file);
	fd_in = open(trimmed, O_RDONLY);
	if (fd_in < 0)
		perror("minishell: ");
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

void	redirect_input(char	**cmd)
{
	int		fd_out;
	char	*temp[2];
	int		*s_l;
	int		flag;

	s_l = malloc(sizeof(int) * 3);
	fd_out = open("temp_input", O_RDWR | O_TRUNC | O_CREAT, 0777);
	flag = 0;
	while (find_redirect_file(*cmd, '<', s_l))
	{
		flag = copy_file(ft_substr(*cmd, s_l[0], s_l[1]), fd_out);
		temp[0] = ft_substr(*cmd, 0, s_l[0]);
		temp[1] = ft_substr(*cmd, s_l[0] + s_l[1], ft_strlen(*cmd));
		free(*cmd);
		*cmd = ft_strjoin(temp[0], temp[1]);
		free(temp[0]);
		free(temp[1]);
	}
	free(s_l);
	if (flag)
	{
		*cmd = trim_free(*cmd, " ");
		dup2(open("temp_input", O_RDONLY), 0);
	}
}

char	**output_files(char **cmd)
{
	char	**files;
	char	*temp[2];
	int		*s_l;
	int		i;

	s_l = malloc(sizeof(int) * 3);
	files = malloc(sizeof(char *) * ft_strlen(*cmd));
	i = 0;
	files[0] = NULL;
	while (find_redirect_file(*cmd, '>', s_l))
	{
		files[i++] = trim_free(ft_substr(*cmd, s_l[0], s_l[1]), " >");
		files[i] = NULL;
		temp[0] = ft_substr(*cmd, 0, s_l[0]);
		temp[1] = ft_substr(*cmd, s_l[0] + s_l[1], ft_strlen(*cmd));
		free(*cmd);
		*cmd = ft_strjoin(temp[0], temp[1]);
		free(temp[0]);
		free(temp[1]);
	}
	free(s_l);
	return (files);
}

int	redirect_output(char **cmd, char **envp)
{
	char	**files;
	pid_t	pid;
	int		i;

	files = output_files(cmd);
	if (files[0] == NULL)
		return (0);
	i = -1;
	while (files[++i])
	{
		pid = fork();
		if (pid == 0)
		{
			redirect_input(cmd);
			dup2(open(files[i], O_RDWR | O_TRUNC | O_CREAT, 0777), 1);
			ft_execute(*cmd, envp);
		}
		else if (pid < 0)
			ft_puterror();
	}
	exit(0);
	return (1);
}
