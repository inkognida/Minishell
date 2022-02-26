/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:15:09 by hardella          #+#    #+#             */
/*   Updated: 2022/02/26 18:43:38 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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