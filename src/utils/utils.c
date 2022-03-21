/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:17:00 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/21 11:46:37 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arr_len(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
		i++;
	return (i);
}

char	**copy_arr(char	**arr)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * (arr_len(arr) + 1));
	i = -1;
	while (arr[++i])
		new[i] = ft_strdup(arr[i]);
	new[i] = NULL;
	return (new);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
