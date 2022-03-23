/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:33:00 by hardella          #+#    #+#             */
/*   Updated: 2022/03/23 19:44:10 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mainelse(int *fd1, int *fd2)
{
	(void)*fd2;
	dup2(*fd1, 0);
}

void	heredoc_helper(int *files)
{
	close(files[1]);
	dup2(files[0], 0);
	wait(NULL);
}

int	ft_strlen_pipex(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_findpath(char *cmd, char **envp)
{
	char	**paths;
	char	*single_path;
	char	*used_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr_pipex(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == (void *)0)
		ft_error_file("minishell", "command not found", cmd, 127);
	paths = ft_split_pipex(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		used_path = ft_strjoin_pipex(paths[i++], "/");
		if (used_path == NULL)
			ft_puterror();
		single_path = ft_strjoin_pipex(used_path, cmd);
		if (single_path == NULL)
			ft_putmallocerror(used_path);
		free(used_path);
		if (access(single_path, F_OK) == 0)
			return (single_path);
	}
	return (NULL);
}
