/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:08:39 by hardella          #+#    #+#             */
/*   Updated: 2022/03/25 20:45:02 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_args_helper(char *valid, char ***args, char delim)
{
	int	i;
	int	j;

	free(valid);
	i = -1;
	while ((*args)[++i])
	{
		j = -1;
		while ((*args)[i][++j])
			if ((*args)[i][j] == -1)
				(*args)[i][j] = delim;
	}
}

char	*get_and_free(char *valid)
{
	char	*temp;

	temp = valid_string(valid);
	free(valid);
	return (temp);
}

char	**split_args(char *str, char delim, int remove)
{
	char	*valid;
	char	**args;
	int		i;

	i = -1;
	valid = ft_strdup(str);
	if (valid == NULL)
		return (NULL);
	while (valid[++i])
	{
		if (valid[i] == '\'')
			while (valid[++i] != '\'' && valid[i])
				if (valid[i] == delim)
					valid[i] = -1;
		if (valid[i] == '"')
			while (valid[++i] != '"' && valid[i])
				if (valid[i] == delim)
					valid[i] = -1;
	}
	if (remove)
		valid = get_and_free(valid);
	args = ft_split(valid, delim);
	split_args_helper(valid, &args, delim);
	return (args);
}
