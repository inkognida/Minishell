/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:02:21 by hardella          #+#    #+#             */
/*   Updated: 2022/03/08 23:35:19 by yironmak         ###   ########.fr       */
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
		return (1);
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
		ft_error_file("cd", "no such file or directory", path, 1);
	env_edit("OLDPWD", old, env);
	env_edit("PWD", new, env);
	if (path != NULL)
		free(new);
	return (0);
}

int	ft_cd(char **args, t_list **env)
{
	char	*temp;
	char	*old;
	char	*new;

	new = NULL;
	if (args == NULL || *args == NULL || env == NULL)
		return (1); //something to do
	if (arr_len(args) > 3)
		ft_error("cd", "too many arguments", -1);
	if (arr_len(args) == 1)
		return (ft_cd_home(env, NULL));
	else if (arr_len(args) == 2)
	{
		if (args[1][0] == '~')
			return (ft_cd_home(env, args[1]));
		if (chdir(args[1]) == -1)
			ft_error_file("cd", "no such file or directory", args[1], -1);
		old = env_find("PWD", *env);
		env_edit("OLDPWD", old, env);
		new = getcwd(new, 1000);
		env_edit("PWD", new, env);
		free(new);
	}
	return (0);
	// free args!
}

int	ft_env(t_list *env, char **args)
{
	if (args[1])
		ft_error_file("env", args[1], "No such file or directory", 127);
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

void	ft_exit(char **args, t_list **env)
{
	int	status;

	status = ft_atoi(args[0] + 4);
	//free(args);
	//(env);
	exit(status);
}

//export

int	ft_export_show(t_list *env)
{
	char	**arr;
	char	*temp;
	int		i;
	int		j;

	arr = convert_list_to_arr(env);
	i = 0;
	while (i < arr_len(arr) - 1)
	{
		j = i + 1;
		while (j < arr_len(arr))
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = -1;
	while (arr[++i])
		printf("%s\n", arr[i]);
	return (0);
}

int	is_valid_for_export(char **k_v)
{
	int	i;
	int	flag;
	
	i = -1;
	while (k_v[0][++i])
		if (ft_isdigit(k_v[0][i]) == 1)
			return (-1);
	if (ft_strlen(k_v[1]))
		return (-2);
	return (1);
}

int	ft_export(char **args, t_list **env)
{
	int		i;
	char	**k_v;

	if (args[1] == NULL)
		return(ft_export_show(*env));
	i = 1;
	while (args[i])
	{
		k_v = ft_split(args[i], '=');
		if (arr_len(k_v) != 2)
		if (is_valid_for_export(args[i]) == 1)
			ft_error_file("export", "not an identifier", k_v[0], 1);
		
	}
}
//export

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0 ||\
	ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0 ||\
	ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0 ||\
	ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 ||\
	ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0 ||\
	ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 ||\
	ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

int	own_execve(char *exec_cmd, char **args, t_list *env)
{
	if (ft_strncmp(exec_cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		return (ft_pwd(args, env));
	else if (ft_strncmp(exec_cmd, "env", ft_strlen("env")+1) == 0)
		return (ft_env(env, args));
	else if (ft_strncmp(exec_cmd, "export", ft_strlen("env")+1) == 0)
		return (ft_export(args, &env));
	//need to add all cmds
	
	return (-1);
}