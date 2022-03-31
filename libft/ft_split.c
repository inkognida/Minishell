/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:54:58 by hardella          #+#    #+#             */
/*   Updated: 2022/03/25 20:41:44 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	static	count_substrings(char const *s, char c)
{
	int		count;
	size_t	i;

	i = 0;
	while (s[i] == c)
		i++;
	if (s[i] != c)
	{
		count = 1;
		while (s[i] && s[i] != c)
			i++;
	}
	while (s[i] && i < ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
		{
			count++;
			while (s[i] == c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**free_arr(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
	return (NULL);
}

static char	**fill_strs(char **strs, char const *s, char c)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = -1;
	while (strs && i < (int)ft_strlen(s))
	{
		len = 0;
		while (s[i] != c && s[i])
		{
			len++;
			i++;
		}
		i++;
		if (len == 0)
			continue ;
		strs[++j] = ft_substr(s, i - len - 1, len);
		if (strs[j] == NULL)
			return (free_arr(strs));
	}
	strs[++j] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (count_substrings(s, c) + 1));
	if (strs == NULL)
		return (NULL);
	strs = fill_strs(strs, s, c);
	return (strs);
}
