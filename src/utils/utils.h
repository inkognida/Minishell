/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:38:55 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/19 21:41:15 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

char	**copy_arr(char	**arr);
int		arr_len(char **cmds);
void	free_arr(char **arr);

void	env_edit(char *key, char *value, t_list **env);
char	*env_find(char *key, t_list *lst);
void	env_remove(char *key, t_list **env);
void	init_envp(t_list **env, char **envp);
char	**convert_list_to_arr(t_list *env);

void	ft_puterror(void);
int		ft_error(char *from, char *message, int exit_flag);
int		ft_error_file(char *from, char *file, char *message, int exit_flag);
void	ft_putmallocerror(char *str);

#endif