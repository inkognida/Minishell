/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:53:14 by hardella          #+#    #+#             */
/*   Updated: 2022/03/23 16:01:53 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char *cmd, t_list *envp)
{
	char	**args;
	char	**env;

	env = convert_list_to_arr(envp);
	args = split_args(ft_strtrim(cmd, " "), ' ', 1);
	if (args == NULL || envp == NULL)
		exit(1);
	else if (ft_strnstr(args[0], "/", ft_strlen(args[0])))
	{
		if (execve(args[0], args, env) == -1)
			ft_error_file("minishell", "command not found", cmd, 127);
	}
	else if (is_builtin(args[0]) == 1)
	{
		if (own_execve(args[0], args, envp) == -1)
			ft_error_file("minishell", "command not found", cmd, 127);
		exit(0);
	}
	else
	{
		if (execve(ft_findpath(args[0], env), args, env) == -1)
			ft_error_file("minishell", "command not found", cmd, 127);
	}
}

void	init_prc(t_pipex *prc, char **cmds)
{
	prc->fifo[0][0] = -1;
	prc->fifo[0][1] = -1;
	prc->fifo[1][0] = -1;
	prc->fifo[1][1] = -1;
	prc->cur_pipe = 0;
	prc->i = 0;
	prc->len = arr_len(cmds);
}

void	child(t_pipex *prc, char **cmds, t_list *envp)
{
	if (prc->i > 0)
	{
		dup2(prc->fifo[1 - prc->cur_pipe][0], STDIN_FILENO);
		close(prc->fifo[1 - prc->cur_pipe][0]);
	}
	if (prc->i < prc->len - 1 && prc->len > 1)
	{
		dup2(prc->fifo[prc->cur_pipe][1], STDOUT_FILENO);
		close(prc->fifo[prc->cur_pipe][0]);
		close(prc->fifo[prc->cur_pipe][1]);
	}
	ft_execute(cmds[prc->i], envp);
}

void	ft_pipe(char **cmds, t_list *envp)
{
	t_pipex	prc;

	init_prc(&prc, cmds);
	while (prc.i < prc.len)
	{
		if (pipe(prc.fifo[prc.cur_pipe]) == -1)
			ft_puterror();
		prc.pid = fork();
		if (prc.pid == -1)
			ft_puterror();
		if (prc.pid == 0)
			child(&prc, cmds, envp);
		close(prc.fifo[1 - prc.cur_pipe][0]);
		close(prc.fifo[prc.cur_pipe][1]);
		prc.cur_pipe = 1 - prc.cur_pipe;
		prc.i++;
	}
	close(prc.fifo[1 - prc.cur_pipe][0]);
	prc.i = 0;
	while (prc.i < prc.len)
	{
		waitpid(-1, 0, 0);
		prc.i++;
	}
}

void	pipex(char **cmds, t_list *envp, char *file, char mode)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (file)
		{
			close(1);
			if (mode == 'w')
				open(file, O_WRONLY | O_TRUNC, 0777);
			else if (mode == 'a')
				open(file, O_WRONLY | O_APPEND, 0777);
		}
		ft_pipe(cmds, envp);
		exit(0);
	}
	else if (pid < 0)
		ft_puterror();
	else
		waitpid(pid, 0, 0);
}
