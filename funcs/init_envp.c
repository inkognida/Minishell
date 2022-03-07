/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:06:18 by hardella          #+#    #+#             */
/*   Updated: 2022/03/07 15:41:25 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/minishell.h"

void	init_envp(t_list **env, char **envp)
{
	int		i;
	char	*tmp;
	t_list	*env_tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strdup(envp[i]);
		if (tmp == NULL)
			exit(1);
		env_tmp = ft_lstnew(tmp);
		if (env_tmp == NULL)
			exit(1);
		ft_lstadd_back(env, env_tmp);
		i++;
	}
}