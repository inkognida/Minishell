/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:53:14 by hardella          #+#    #+#             */
/*   Updated: 2022/02/26 18:36:22 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_execute(char *cmd1, char **envp)
{
	char	**cmds;

	cmds = ft_split_pipex(cmd1, ' ');
	if (!(envp))
		ft_puterror();
	if (execve(ft_findpath(cmds[0], envp), cmds, envp) == -1)
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
		ft_execute(cmd, envp);
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