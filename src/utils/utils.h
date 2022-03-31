/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:38:55 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/25 20:29:47 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

char	**copy_arr(char	**arr);
int		arr_len(char **cmds);
void	free_arr(char **arr);
int		otkrovenniy_kostil(char	**arr, int code);

void	env_edit(char *key, char *value, t_list **env);
char	*env_find(char *key, t_list *lst);
void	env_remove(char *key, t_list **env);
void	init_envp(t_list **env, char **envp);
char	**convert_list_to_arr(t_list *env);

void	ft_puterror(void);
int		ft_error(char *from, char *message, int exit_flag);
int		ft_error_file(char *from, char *file, char *message, int exit_flag);
void	ft_putmallocerror(char *str);
int		ft_error_export_free(char *from, char *file, char **k_v);

char	*null_valid(char *valid_str, int j);
int		continue_valid(char *str, int *i);
char	*valid_helper(char *str, char *valid_str, int i, int j);
char	*valid_string(char *str);
void	split_args_helper(char *valid, char ***args, char delim);
char	**split_args(char *str, char delim, int remove);

int		free_env(t_list *env);
void	not_valid_string(void);
int		ft_isspace(int c);
int		invalid_str(char *str);
void	signals(void);
char	*get_env_name(char *str, int i, t_list *env);
void	env_variables_helper_one(char *tmps[2], char *str, int *i);
void	env_variables_helper_two(char *tmps[2], char *str, int *i, t_list *env);
int		env_variables_help(char *str, int *i);
void	ilya_spasibo_za_detstvo(char *tmps[2], int *i, char *str, t_list *env);
void	loop_env_variables(char *tmps[2], char *str, int i, t_list *env);
char	*env_variables(char *str, t_list *env);
char	*ft_strncat(char *dest, char *src, int nb);
char	*update_exit(void);
int		free_arrs(char **arr1, char **arr2, int f1, int f2);

#endif