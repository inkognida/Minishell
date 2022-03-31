/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:02:21 by hardella          #+#    #+#             */
/*   Updated: 2022/03/25 20:44:43 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

int	ft_env(t_list *env, char **args)
{
	if (args[1])
		ft_error_file("env", args[1], "No such file or directory", 127);
	while (env)
	{
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
	return (0);
}

int	ft_echo(char *cmd, char **args)
{
	int	i;
	int	flag;

	(void)cmd;
	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	flag = 1;
	if (!ft_strncmp(args[1], "-n", 3))
	{
		i++;
		flag = 0;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[++i])
			write(1, " ", 1);
	}
	if (flag == 1)
		write(1, "\n", 1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0 || \
	ft_strncmp(cmd, "pwd", 4) == 0 || \
	ft_strncmp(cmd, "env", 4) == 0 || \
	ft_strncmp(cmd, "export", 7) == 0 || \
	ft_strncmp(cmd, "unset", 6) == 0 || \
	ft_strncmp(cmd, "export", 7) == 0 || \
	ft_strncmp(cmd, "exit", 5) == 0 || \
	ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	return (0);
}

int	own_execve(char *exec_cmd, char **args, t_list *env)
{
	if (ft_strncmp(exec_cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		g_exit_status = ft_pwd(args, env);
	else if (ft_strncmp(exec_cmd, "env", ft_strlen("env") + 1) == 0)
		g_exit_status = ft_env(env, args);
	else if (ft_strncmp(exec_cmd, "export", ft_strlen("export") + 1) == 0)
		g_exit_status = ft_export(args, &env);
	else if (ft_strncmp(exec_cmd, "unset", ft_strlen("unset") + 1) == 0)
		g_exit_status = ft_unset(args, &env);
	else if (ft_strncmp(exec_cmd, "echo", ft_strlen("echo") + 1) == 0)
		g_exit_status = ft_echo(exec_cmd, args);
	if (g_exit_status != -1)
		return (g_exit_status);
	return (-1);
}

int	try_builtins(char **cmds, t_list **env)
{
	int		len;
	char	**args;
	int		status;

	status = 0;
	len = arr_len(cmds);
	args = split_args(cmds[len - 1], ' ', 1);
	if (args == NULL)
	{
		free(args);
		return (-1);
	}
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (ft_cd(args, env));
	if (ft_strncmp(args[0], "export", 3) == 0 && args[1])
		return (ft_export(args, env));
	if (ft_strncmp(args[0], "unset", 3) == 0)
		return (ft_unset(args, env));
	if (ft_strncmp(args[0], "exit", 5) == 0)
		ft_exit(args, env);
	free_arr(args);
	return (-1);
}
