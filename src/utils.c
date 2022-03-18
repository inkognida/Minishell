/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:17:00 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/05 18:18:03 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*trim_free(char *str, char *charset)
{
	char	*trimmed;

	trimmed = ft_strtrim(str, charset);
	free(str);
	return (trimmed);
}

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
