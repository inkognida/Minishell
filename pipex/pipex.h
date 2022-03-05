/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:04:44 by hardella          #+#    #+#             */
/*   Updated: 2022/03/04 21:15:19 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>

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
void		ft_execute(char *cmd1, char **envp);
int			ft_open(char *filename, int flag);
void		ft_heredoc(char *limiter);
void		ft_chpar(char *cmd, char **envp);
void		pipex(char **cmds, char **envp);
int			len_cmds(char **cmds);


void		multi_pipe(char *cmd1, char **envp);

#endif