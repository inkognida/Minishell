/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:17:00 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/25 20:29:38 by yironmak         ###   ########.fr       */
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

int	free_arrs(char **arr1, char **arr2, int f1, int f2)
{
	if (f1)
		free_arr(arr1);
	if (f2)
		free_arr(arr2);
	return (1);
}

int	otkrovenniy_kostil(char	**arr, int code)
{
	free(arr);
	return (code);
}
