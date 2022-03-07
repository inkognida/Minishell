/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:02:21 by hardella          #+#    #+#             */
/*   Updated: 2022/03/07 17:17:29 by hardella         ###   ########.fr       */
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

void	go_pwd(char *exec_cmd, char **args, t_list *env)
{
	char	*pwd;

	if (exec_cmd == NULL || args == NULL || *args == NULL || envp == NULL)
		return ; //should be exit(code)
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return ; //should be exit(code)
	printf("%s\n", pwd);
	
}

void	go_cd(char *exec_cmd, char **args, t_list **env)
{
	int	i;

	i = 0;
	if (exec_cmd == NULL || args == NULL || *args == NULL || envp == NULL)
		return ; //something to do
	if (!args[1])
		return ; //something to do
	while (env[i] != NULL)
	{
		if ()
	
	}
	return ;
}

int	own_execve(char *exec_cmd, char **args, t_list *envp)
{
	if (ft_strncmp(exec_cmd, "cd", ft_strlen("cd")+1) == 0)
		go_cd(exec_cmd, args, &envp);
	else if (ft_strncmp(exec_cmd, "pwd", ft_strlen("pwd")+1) == 0)
		go_pwd(exec_cmd, args, envp);
	//need to add all cmds
	return (-1);
}