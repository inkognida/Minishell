/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:15:09 by hardella          #+#    #+#             */
/*   Updated: 2022/03/19 20:46:41 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/gnl.h"
# include <limits.h>

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char	*string;
	int		flag;
	t_cmd	*next;
}				t_cmd;

typedef struct s_pipex
{
	pid_t	pid;
	int		i;
	int		len;
	int		fifo[2][2];
	int		cur_pipe;

}				t_pipex;

char	**split_args(char *str, char delim);
int		try_builtins(char **cmds, t_list **env);

int		redirect_input(char	**cmd);
void	redirect_output(char **cmds, char **files, t_list *env, int input_flag);
int		copy_file(char	*in_file, int fd_out);
void	just_copy(char **files);
char	**find_files(char **cmd, char *type);
void	create_files(char **files);

char	*trim_free(char *str, char *charset);
void	handle_signal(int sig);
void	exe(char *cmd, char **envp);
char	**copy_arr(char	**arr);
int		arr_len(char **cmds);

void	env_edit(char *key, char *value, t_list **env);
char	*env_find(char *key, t_list *lst);
void	env_remove(char *key, t_list **env);

char	**convert_list_to_arr(t_list *env);
void	init_envp(t_list **env, char **envp);
void	display(t_list *env);
void	display_arr(char **envp);


int		own_execve(char *exec_cmd, char **args, t_list *env);
int		own_cmds(char *cmd);
int		ft_cd(char **args, t_list **env);
int		is_builtin(char *cmd);
void	ft_exit(char **args, t_list **env);
int		ft_export(char **args, t_list **env);
int		ft_unset(char **args, t_list **env);

void	pipex(char **cmds, t_list *envp, char *file, char mode);

void	ft_puterror(void);
int		ft_error(char *from, char *message, int exit_flag);
int		ft_error_file(char *from, char *file, char *message, int exit_flag);
void	ft_putmallocerror(char *str);

char	**ft_split_pipex(char const *s, char c);
char	*ft_strjoin_pipex(char *s1, char *s2);
char	*ft_strnstr_pipex(char *haystack, char *needle, int len);
int		ft_strncmp_pipex(char *s1, char *s2, int n);
char	*ft_findpath(char *cmd, char **envp);
void	heredoc_helper(int *files);
void	ft_bonus_helper(int fd1, int fd2, char **cmds, char **envp);
void	ft_mainelse(int *fd1, int *fd2);
void	ft_bonuserror(void);
void	ft_putmallocerror(char *str);
void	ft_puterror(void);
int		ft_error(char *from, char *message, int exit_flag);
int		ft_error_file(char *from, char *file, char *message, int exit_flag);
int		ft_strlen_pipex(const char *s);
void	ft_execute(char *cmd, t_list *env);
int		ft_open(char *filename, int flag);
void	ft_chpar(char *cmd, t_list *env);
int		len_cmds(char **cmds);

void	work_pipex(char **cmds, t_list *env);

#endif