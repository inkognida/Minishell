/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:15:09 by hardella          #+#    #+#             */
/*   Updated: 2022/03/08 23:00:53 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "gnl.h"
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include <limits.h>

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char	*string;
	int		flag;
	t_cmd	*next;
}				t_cmd;

char	**split_args(char *str, char delim);
void	redirect_input(char	**cmd);
int		redirect_output(char **cmd, char **envp);
char	*trim_free(char *str, char *charset);
void	handle_signal(int sig);
void	exe(char *cmd, char **envp);
char	**output_files(char **cmd);
char	**copy_arr(char	**arr);
int		arr_len(char **cmds);

void	env_edit(char *key, char *value, t_list **env);
char	*env_find(char *key, t_list *lst);

char	**convert_list_to_arr(t_list *env);
void	init_envp(t_list **env, char **envp);
void	display(t_list *env);
void	display_arr(char **envp);

int		own_execve(char *exec_cmd, char **args, t_list *env);
int		own_cmds(char *cmd);
int		ft_cd(char **args, t_list **env);
int		is_builtin(char *cmd);
void	ft_exit(char **args, t_list **env);

#endif