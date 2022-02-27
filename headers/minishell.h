/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:15:09 by hardella          #+#    #+#             */
/*   Updated: 2022/02/27 19:28:54 by hardella         ###   ########.fr       */
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

typedef struct s_cmds
{
	int		cmd;
	char	**split;
}				t_cmds;

#endif