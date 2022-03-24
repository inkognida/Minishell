/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:04:57 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/24 15:14:16 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**find_files(char **cmd, char *type)
{
	char	**files;
	char	*temp[2];
	int		*s_l;
	int		i;

	files = malloc(sizeof(char *) * ft_strlen(*cmd));
	if (files == NULL)
		return (NULL);
	files[0] = NULL;
	s_l = malloc(sizeof(int) * 3);
	i = 0;
	while (find_redirect_file(*cmd, type, s_l))
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

void	redirect_output(char **cmds, char **files, t_list *env, int input_flag)
{
	int		i;
	char	**cmds_copy;
	char	*trimmed;

	i = -1;
	while (files[++i])
	{
		cmds_copy = copy_arr(cmds);
		if (files[i][1] == '>')
			trimmed = ft_strtrim(files[i] + 2, " ");
		else
			trimmed = ft_strtrim(files[i] + 1, " ");
		if (input_flag)
		{
			close(0);
			open(".temp_input", O_RDONLY);
		}
		if (files[i][1] == '>')
			pipex(cmds_copy, env, trimmed, 'a');
		else
			pipex(cmds_copy, env, trimmed, 'w');
		free_arr(cmds_copy);
		free(trimmed);
	}
}

void	create_files(char **files)
{
	int		i;
	char	*trimmed;

	i = -1;
	while (files[++i])
	{
		trimmed = ft_strtrim(files[i], " >");
		if (files[i][1] == '>')
			close(open(trimmed, O_WRONLY | O_CREAT, 0777));
		else
			close(open(trimmed, O_WRONLY | O_CREAT | O_TRUNC, 0777));
		free(trimmed);
	}
}
