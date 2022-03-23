/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:22:37 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/23 16:05:02 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	*old;
	char	*new;

	new = NULL;
	if (args == NULL || *args == NULL || env == NULL)
		return (1);
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

void	ft_exit(char **args, t_list **env)
{
	int	status;

	(void)env;
	status = ft_atoi(args[0] + 4);
	exit(status);
}
