/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:53:14 by hardella          #+#    #+#             */
/*   Updated: 2022/03/04 21:50:20 by yironmak         ###   ########.fr       */
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

void	exe(char *cmd, char **envp)
{
	char	**args;

	// printf("%s\n", cmd);
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

void	ft_execute(char *cmd, char **envp)
{
	redirect_input(&cmd); // говно из жопы
	if (redirect_output(&cmd, envp))
		return ;
	else
	{
		exe(cmd, envp);
	}
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



// void	exec_cmds(char *cmd, char **envp)
// {
// 	pid_t	parent;

// 	parent = fork();
// 	if (parent == -1)
// 		ft_puterror();
// 	if (parent == 0)
// 		ft_execute(cmd, envp);
// 	else
// 		waitpid(parent, NULL, 0);
// }

// void	pipex(char **cmds, char **envp)
// {
// 	int		fd1;
// 	int		fd2;
// 	int		i;

// 	// if (ft_strncmp_pipex(argv[1], "here_doc",
// 	// 	ft_strlen_pipex(argv[1])) == 0)
// 	// {
// 	// 	flag = 3;
// 	// 	fd2 = ft_open(argv[argc - 1], 1);
// 	// 	ft_heredoc(argv[2]);
// 	// }
// 	// else
// 	// {
// 	// 	flag = 2;
// 	ft_mainelse(&fd1, &fd2);
// 	// }
// 	i = 0;
	
// 	// printf("%d %s\n", len_cmds(cmds), cmds[0]);
// 	while (i < len_cmds(cmds))
// 	{
// 		ft_chpar(cmds[i++], envp);
// 		// printf("%s %d\n", cmds[i], len_cmds(cmds));
// 		// exec_cmds(ft_strtrim(cmds[i++], " \t"), envp);
// 	}
// 	ft_bonus_helper(fd2, fd1, cmds, envp); //waitpid handler

// }

