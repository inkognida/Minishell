/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:02:21 by hardella          #+#    #+#             */
/*   Updated: 2022/03/07 20:10:42 by yironmak         ###   ########.fr       */
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
	//need to add all
	return (0);
}

int ft_pwd(char **args, t_list *env)
{
	char pwd[PATH_MAX];

	if (args[1] != NULL)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	if (env == NULL)
		return (1);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (1);
	printf("%s\n", pwd);
	return (0);
}

int	ft_cd_home(t_list **env, char *path)
{
	char	*old;
	char	*new;
	int		new_len;
	char	buf[1000];

	old = env_find("PWD", *env);
	if (path == NULL)
		new = env_find("HOME", *env);
	else
	{
		new_len = ft_strlen(env_find("HOME", *env)) + ft_strlen(path) + 1;
		new = malloc(new_len);
		ft_strlcat(new, env_find("HOME", *env), new_len);
		ft_strlcat(new, path + 1, new_len);
	}
	if (chdir(new) == -1)
		perror("hz");
	printf("%d\n", chdir(new));
	env_edit("OLDPWD", old, env);
	env_edit("PWD", new, env);
	printf("new %s %s\n", new, env_find("PWD", *env));
	getcwd(buf,1000);
	printf("safdasdf %s\n", buf);
	ft_pwd(NULL, *env);
	if (path != NULL)
		free(new);
	return (0);
}

int	ft_cd(char **args, t_list **env)
{
	char	*temp;

	if (args == NULL || *args == NULL || env == NULL)
		return (1); //something to do
	if (arr_len(args) > 3)
		ft_error("cd", "too many arguments", 1);
	if (arr_len(args) == 2 && args[1][0] == '~')
		return (ft_cd_home(env, args[1]));
	if (arr_len(args) == 1)
		return (ft_cd_home(env, NULL));
	return (0);
}

int	own_execve(char *exec_cmd, char **args, t_list *envp)
{
	if (ft_strncmp(exec_cmd, "cd", ft_strlen(exec_cmd)) == 0)
		ft_cd(args, &envp);
	else if (ft_strncmp(exec_cmd, "pwd", ft_strlen(exec_cmd)) == 0)
		ft_pwd(args, envp);
	//need to add all cmds
	else
		return (-1);
}