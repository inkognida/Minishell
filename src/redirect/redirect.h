/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:34:24 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/19 21:35:56 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "../minishell.h"

int		redirect_input(char	**cmd);
void	redirect_output(char **cmds, char **files, t_list *env, int input_flag);
int		copy_file(char	*in_file, int fd_out);
void	just_copy(char **files);
char	**find_files(char **cmd, char *type);
void	create_files(char **files);

#endif