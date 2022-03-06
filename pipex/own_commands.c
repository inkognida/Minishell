/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:02:21 by hardella          #+#    #+#             */
/*   Updated: 2022/03/06 20:34:46 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

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