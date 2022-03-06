/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:04:44 by hardella          #+#    #+#             */
/*   Updated: 2022/03/06 19:54:27 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		i;
	int		len;
	int		fifo[2][2];
	int		cur_pipe;

}				t_pipex;

char		**ft_split_pipex(char const *s, char c);
char		*ft_strjoin_pipex(char *s1, char *s2);
char		*ft_strnstr_pipex(char *haystack, char *needle, int len);
int			ft_strncmp_pipex(char *s1, char *s2, int n);
char		*ft_findpath(char *cmd, char **envp);
void		heredoc_helper(int *files);
void		ft_bonus_helper(int fd1, int fd2, char **cmds, char **envp);
void		ft_mainelse(int *fd1, int *fd2);
void		ft_bonuserror(void);
void		ft_putmallocerror(char *str);
void		ft_puterror(void);
int			ft_strlen_pipex(const char *s);
void		ft_execute(char *cmd, char **envp);
int			ft_open(char *filename, int flag);
void		ft_heredoc(char *limiter);
void		ft_chpar(char *cmd, char **envp);
void		pipex(char **cmds, char **envp);
int			len_cmds(char **cmds);

void		work_pipex(char **cmds, char **envp);

#endif