/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:53:14 by hardella          #+#    #+#             */
/*   Updated: 2022/03/05 19:44:17 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_open(char *filename, int flag)
{
	if (flag == 0)
	{
		if (access(filename, F_OK))
			ft_puterror();
		return (open(filename, O_RDONLY, 0777));
	}
	else
		return (open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777));
}

void	ft_execute(char *cmd, char **envp)
{
	char	**args;

	args = split_args(ft_strtrim(cmd, " "), ' ');
	if (args == NULL)
		exit(1); //free need
	if (!(envp))
		ft_puterror();
	if (ft_strnstr(args[0], "/", ft_strlen(args[0])))
	{
		if (execve(args[0], args, envp) == -1)
			ft_puterror();
	}
	else
		if (execve(ft_findpath(args[0], envp), args, envp) == -1)
			ft_puterror();
}

// void	ft_execute(char *cmd, char **envp)
// {
// 	// if (redirect_output(&cmd, envp))
// 	// 	return ;
// 	// else
// 	// {
// 		// redirect_input(&cmd);
// 		exe(cmd, envp);
// 	// }
// }

void	multi_pipe(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	process;
	

	if (pipe(fd) == -1)
		ft_puterror();
	process = fork();
	if (process == -1)
		ft_puterror();
	if (process == 0)
	{
		dup2(fd[1], 1);
		ft_execute(cmd, envp);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
	}
}

void	ft_pipe(char **cmds, int len, char **envp, char *file)
{
	pid_t	pid;
	pid_t	waitall;
	int		i;

	pid = fork();
	if (pid == 0)
	{
		if (file)
		{
			close(1);
			open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
		}
		i = 0;
		while (i < len - 1)
		multi_pipe(cmds[i++], envp);
		waitall = fork();
		if (!waitall)
		{
			ft_execute(cmds[len - 1], envp);
		}
		else
			while (len-- -1)
				waitpid(waitall, NULL, 0);
		exit(0);
	}
	else if (pid < 0)
		ft_puterror();
	else
		waitpid(pid, 0, 0);
}

void	pipex(char **cmds, char **envp)
{
	int		i;
	int 	len;
	char	**files;
	char	**cmds_copy;
	
	i = -1;
	len = arr_len(cmds);
	files = output_files(&(cmds[len - 1]));
	if (files[0] == NULL)
	{
		redirect_input(&(cmds[0]));
		ft_pipe(cmds, len, envp, NULL);
	}
	while (files[++i])
	{
		printf("%s\n", files[i]);
		cmds_copy = copy_arr(cmds);
		redirect_input(&(cmds_copy[0]));
		ft_pipe(cmds_copy, len, envp, files[i]);
		free(cmds_copy);
	}
	exit(0);
}
