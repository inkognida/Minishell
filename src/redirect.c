/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:04:57 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/19 18:39:35 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_redirect_file(char *cmd, char *type, int *start_len_i)
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
		if (ft_strncmp(cmd + start_len_i[2], type, ft_strlen(type)) == 0)
		{
			start_len_i[0] = start_len_i[2];
			start_len_i[2] += 2;
			while (cmd[start_len_i[2]] == ' ')
				start_len_i[2]++;
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
	fd_out = open(".temp_input", O_RDWR | O_TRUNC | O_CREAT, 0777);
	flag = 0;
	while (find_redirect_file(*cmd, "<", s_l))
	{
		flag = copy_file(ft_substr(*cmd, s_l[0], s_l[1]), fd_out);
		temp[0] = ft_substr(*cmd, 0, s_l[0]);
		temp[1] = ft_substr(*cmd, s_l[0] + s_l[1], ft_strlen(*cmd));
		free(*cmd);
		*cmd = ft_strjoin(temp[0], temp[1]);
		free(temp[0]);
		free(temp[1]);
	}
	close(fd_out);
	free(s_l);
	if (flag)
	{
		*cmd = trim_free(*cmd, " ");
		dup2(open(".temp_input", O_RDONLY), 0);
	}
}

char	**find_output_files(char **cmd)
{
	char	**files;
	char	*temp[2];
	int		*s_l;
	int		i;

	files = malloc(sizeof(char *) * ft_strlen(*cmd));
	files[0] = NULL;
	s_l = malloc(sizeof(int) * 3);
	i = 0;
	while (find_redirect_file(*cmd, ">", s_l))
	{
		files[i++] = ft_substr(*cmd, s_l[0], s_l[1]);
		files[i] = NULL;
		temp[0] = ft_substr(*cmd, 0, s_l[0]);
		temp[1] = ft_substr(*cmd, s_l[0] + s_l[1], ft_strlen(*cmd));
		free(*cmd);
		*cmd = ft_strjoin_free(temp[0], temp[1], 1, 1);
	}
	free(s_l);
	return (files);
}

void	redirect_output(char **cmds, char **files, t_list *env)
{
	int		i;
	char	**cmds_copy;
	char	*trimmed;

	i = -1;
	while (files[++i])
	{
		cmds_copy = copy_arr(cmds);
		redirect_input(&(cmds_copy[0]));
		if (files[i][1] == '>')
			trimmed = ft_strtrim(files[i] + 2, " ");
		else
			trimmed = ft_strtrim(files[i] + 1, " ");
		if (files[i][1] == '>')
			pipex(cmds_copy, env, trimmed, 'a');
		else
			pipex(cmds_copy, env, trimmed, 'w');
		free(files[i]);
		free(cmds_copy);
	}
	free(trimmed);
}
