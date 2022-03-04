/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:53:14 by hardella          #+#    #+#             */
/*   Updated: 2022/03/04 13:46:12 by yironmak         ###   ########.fr       */
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

void	ft_execute(char *cmd1, char **args, char **envp)
{
	char	**cmds;

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

void	ft_chpar(char *cmd, char **envp)
{
	int		files[2];
	pid_t	parent;

	if (pipe(files) == -1)
		ft_puterror();
	parent = fork();
	if (parent == -1)
		ft_puterror();
	if (parent == 0)
	{
		close(files[0]);
		dup2(files[1], 1);
		// ft_execute(cmd, envp);  чето сделать!!!
	}
	else
	{
		close(files[1]);
		dup2(files[0], 0);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int		fd1;
// 	int		fd2;
// 	int		flag;

// 	if (argc >= 5)
// 	{
// 		if (ft_strncmp_pipex(argv[1], "here_doc",
// 			ft_strlen_pipex(argv[1])) == 0)
// 		{
// 			flag = 3;
// 			fd2 = ft_open(argv[argc - 1], 1);
// 			ft_heredoc(argv[2]);
// 		}
// 		else
// 		{
// 			flag = 2;
// 			ft_mainelse(&fd1, &fd2, argv, argc);
// 		}
// 		while (flag < argc - 2)
// 			ft_chpar(argv[flag++], envp);
// 		ft_bonus_helper(fd2, argv, argc, envp);
// 	}
// 	else
// 		ft_bonuserror();
// }
