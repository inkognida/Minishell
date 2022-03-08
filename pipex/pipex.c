/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:53:14 by hardella          #+#    #+#             */
/*   Updated: 2022/03/08 22:34:11 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_execute(char *cmd, t_list *envp)
{
	char	**args;
	char	**env = convert_list_to_arr(envp);
	args = split_args(ft_strtrim(cmd, " "), ' ');
	if (args == NULL || envp == NULL)
		exit(1); //fix that exit (maybe (free()) need)
	else if (ft_strnstr(args[0], "/", ft_strlen(args[0])))
	{
		if (execve(args[0], args, env) == -1)
			ft_puterror();
	}
	else if (own_cmds(args[0]) == 1)
	{
		if (own_execve(args[0], args, envp) == -1)
			ft_puterror();
		exit(0); //end proccess
	}
	else
	{
		if (execve(ft_findpath(args[0], env), args, env) == -1)
			ft_puterror();
	}
}

void	ft_pipe(char **cmds, t_list *envp, char *file)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (file)
		{
			close(1);
			open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
		}
		work_pipex(cmds, envp);
		exit(0);
	}
	else if (pid < 0)
		ft_puterror();
	else
		waitpid(pid, 0, 0);
}

// here is our final pipex (I hope) (check struct in pipex.h)
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

void	work_pipex(char **cmds, t_list *envp)
{
	t_pipex	prc;

	init_prc(&prc, cmds);
	while (prc.i < prc.len)
	{
		if (pipe(prc.fifo[prc.cur_pipe]) == -1)
			ft_puterror(); //special code
		prc.pid = fork();
		if (prc.pid == -1)
			ft_puterror(); //special code
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
// end of out ideal pipex

int	try_builtins(char **cmds, t_list *env)
{
	char 	*trimmed;
	int 	len;
	char	**args;
	
	len = arr_len(cmds);
	args = split_args(cmds[len - 1], ' ');
	if (ft_strncmp(args[0], "cd", 3) == 0)
	{
		ft_cd(args, &env);
		return (1);
	}
	if (ft_strncmp(args[0], "exit", 5) == 0)
		ft_exit(args, env);
	return (0);
}

//should include work_pipex here
void	pipex(char **cmds, t_list *env)
{
	int		i;
	int 	len;
	char	**files;
	char	**cmds_copy;
	
	i = -1;
	len = arr_len(cmds);
	files = output_files(&(cmds[len - 1]));
	while (files[++i])
		close(open(files[i], O_RDWR | O_TRUNC | O_CREAT, 0777));
	if (try_builtins(cmds, env))
		return ;
	if (files[0] == NULL)
	{
		redirect_input(&(cmds[0]));
		ft_pipe(cmds, env, NULL);
	}
	i = -1;
	while (files[++i])
	{
		printf("%s\n", files[i]);
		cmds_copy = copy_arr(cmds);
		redirect_input(&(cmds_copy[0]));
		ft_pipe(cmds_copy, env, files[i]);
		free(cmds_copy);
	}
	// exit(0);
}


