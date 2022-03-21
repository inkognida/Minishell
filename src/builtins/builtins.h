/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:28:41 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/19 21:33:43 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

int		own_execve(char *exec_cmd, char **args, t_list *env);
int		try_builtins(char **cmds, t_list **env);
int		is_builtin(char *cmd);
int		ft_echo(char *cmd, char **args);
int		ft_env(t_list *env, char **args);
void	ft_exit(char **args, t_list **env);
int		ft_cd(char **args, t_list **env);
int		ft_pwd(char **args, t_list *env);
int		ft_export(char **args, t_list **env);
int		ft_unset(char **args, t_list **env);

#endif