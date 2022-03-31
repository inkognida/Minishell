/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:06:44 by hardella          #+#    #+#             */
/*   Updated: 2022/04/01 00:13:42 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*null_valid(char *valid_str, int j)
{
	valid_str[j] = '\0';
	return (valid_str);
}

int	continue_valid(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		return (1);
	}
	else if (str[*i] == '"')
		return (2);
	return (0);
}

char	*valid_helper(char *str, char *valid_str, int i, int j)
{
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'' && str[i])
				valid_str[j++] = str[i];
			if (continue_valid(str, &i) == 1 || continue_valid(str, &i) == 2)
				continue ;
			else if (str[i] == '\0')
				return (NULL);
		}
		if (str[i] == '"')
		{
			while (str[++i] != '"' && str[i])
				valid_str[j++] = str[i];
			if (str[i++] == '"')
				continue ;
			if (str[--i] == '\'')
				continue ;
			else if (str[i] == '\0')
				return (NULL);
		}
		valid_str[j++] = str[i++];
	}
	return (null_valid(valid_str, j));
}

char	*valid_string(char *str)
{
	char	*valid_str;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	valid_str = malloc(sizeof(char) * ft_strlen(str));
	if (valid_str == NULL)
		return (NULL);
	temp = valid_helper(str, valid_str, i, j);
	if (temp == NULL)
	{
		free(valid_str);
		return (NULL);
	}
	else
		valid_str = temp;
	return (valid_str);
}
