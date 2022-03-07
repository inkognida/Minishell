/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:02:21 by hardella          #+#    #+#             */
/*   Updated: 2022/03/07 20:29:33 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	own_cmds(char *cmd)
{
	if (cmd == NULL)
		return (0);
	// else if (ft_strncmp(cmds[0], "echo", ft_strlen(cmds[0])) == 0)
	// 	return (1);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd")+1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")+1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen("env")+1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen("env")+1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit")+1) == 0)
		return (1)
	return (0);
}

int	ft_pwd(char **args, t_list *env)
{
	char	pwd[PATH_MAX];

	if (args[1] != NULL)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	if (args == NULL || *args == NULL || env == NULL)
		return (1);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	printf("%s\n", pwd);
	return (0);
}

int	ft_cd(char **args, t_list **env)
{
// 	int	i;

// 	i = 0;
// 	if (args == NULL || *args == NULL || env == NULL)
// 		return ; //something to do
// 	if (!args[1])
// 		return ; //something to do
// 	while (env[i] != NULL)
// 	{
// 		if ()
// 	}
	return (0);
}

int	ft_env(t_list *env, char **args)
{
	char	**env_tmp;
	int		i;	

	if (args[1] != NULL)
	{
		ft_putstr_fd("env: aboba: No such file or directory\n", 2);
		return (1);
	}
	env_tmp = convert_list_to_arr(env);
	i = 0;
	if (env_tmp == NULL)
		return (1);
	while (env_tmp[i])
		printf("%s\n", env_tmp[i++]);
	return (0);
}

int	ft_exit(int	exit_status)
{
	exit(exit_status);
	return (exit_status);
}



//export

int	parse_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '=' && arg[i])
	{
		if (ft_isdigit(arg[i]) == 1)
			return (0);
		i++;
	}
	if (arg[i] == '\0')
		return (0);
	
}

int	ft_export(char **args, t_list **env)
{
	//need to know error status
	int	i;
	char *tmp;

	i = 1;
	if (args[1] == NULL)
	{
		//show sorted env
		return (0);
	}
	return (0);
	// while (args[i])
	// {
	// 	if (args[i] && parse_arg(args[i]) == 1)
	// }
	
	
}
//export



int	own_execve(char *exec_cmd, char **args, t_list *envp)
{
	if (ft_strncmp(exec_cmd, "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(args, &envp));
	else if (ft_strncmp(exec_cmd, "cd", ft_strlen("cd") + 1) == 0)
		return (ft_cd(args, &envp));
	else if (ft_strncmp(exec_cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd(args, envp));
	else if (ft_strncmp(exec_cmd, "env", ft_strlen("env")+1) == 0)
		return (ft_env(envp, args));
	else if (ft_strncmp(exec_cmd, "export", ft_strlen("env")+1) == 0)
		return (ft_env(envp, args));
	else if (ft_strncmp(exec_cmd, "exit", ft_strlen("exit")+1) == 0)
		return (ft_exit(envp));
	//need to add all cmds
	return (-1);
}