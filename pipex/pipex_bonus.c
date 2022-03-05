/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:53:14 by hardella          #+#    #+#             */
/*   Updated: 2022/03/05 17:33:54 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// int	ft_open(char *filename, int flag)
// {
// 	if (flag == 0)
// 	{
// 		if (access(filename, F_OK))
// 			ft_puterror();
// 		return (open(filename, O_RDONLY, 0777));
// 	}
// 	else
// 		return (open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777));
// }


int	own_cmds(char **cmds)
{
	if (cmds == NULL)
		return (0);
	// else if (ft_strncmp(cmds[0], "echo", ft_strlen(cmds[0])) == 0)
	// 	return (1);
	else if (ft_strncmp(cmds[0], "cd", ft_strlen("cd")+1) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "pwd", ft_strlen("pwd")+1) == 0)
		return (1);
	//need to add all
	return (0);
}

void	go_pwd(char **cmd)
{
	char	*pwd;

	if (cmd == NULL || *cmd == NULL)
		return ; //something to do
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return ; //something to do
	printf("%s\n", pwd);
	free(pwd);
	exit(0);
	return ;
}

void	go_cd(char **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return ; //something to do
	chdir(cmd[1]);
	return ;
}

void	own_execve(char **cmds)
{
	if (ft_strncmp(cmds[0], "cd", ft_strlen("cd")+1) == 0)
		go_cd(cmds);
	else if (ft_strncmp(cmds[0], "pwd", ft_strlen("pwd")+1) == 0)
		go_pwd(cmds);
	//need to add all cmds
	return ;
}

void	exe(char *cmd, char **envp)
{
	char	**args;

	args = split_args(ft_strtrim(cmd, " "), ' ');
	if (args == NULL || envp == NULL)
		exit(1); //free need
	else if (own_cmds(args) == 1)
	{
		own_execve(args);
		exit(0); //shit with ctrl + d
	}
	else if (ft_strnstr(args[0], "/", ft_strlen(args[0])))
	{
		if (execve(args[0], args, envp) == -1)
			ft_puterror();
	}
	else
		if (execve(ft_findpath(args[0], envp), args, envp) == -1)
			ft_puterror();
}

void	ft_execute(char *cmd, char **envp)
{
	redirect_input(&cmd); // говно из жопы
	if (redirect_output(&cmd, envp))
		return ;
	else
		exe(cmd, envp);
}

int	len_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
		i++;
	return (i);
}

void	multi_pipe(char *cmd1, char **envp)
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
		close(fd[0]);
		ft_execute(cmd1, envp);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
	}
}

void	pipex(char **cmds, char **envp)
{
	int	i;
	int len;
	pid_t	waitall;
	
	i = 0;
	len = len_cmds(cmds);
	while (i < len - 1)
		multi_pipe(cmds[i++], envp);
	waitall = fork();
	if (!waitall)
		ft_execute(cmds[len - 1], envp);
	else
		while (len-- -1)
			waitpid(waitall, NULL, 0);
	exit(0);
}
