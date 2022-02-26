/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:54:58 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 13:46:31 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(char const *str, char c)
{
	int	i;
	int	co;

	co = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
		{
			while (str[i] != c && str[i])
				i++;
			co++;
		}
	}
	return (co);
}

static char	*word_str(const char *str, int s, int f)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (f - s + 1));
	if (!(word))
		return (NULL);
	while (s < f)
		word[i++] = str[s++];
	word[i] = '\0';
	return (word);
}

static char	**free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (NULL);
}

static char	**kostyl(char const *s, char c)
{
	char	**split;

	if (!(s))
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (words(s, c) + 1));
	return (split);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	int				flag;
	char			**split;

	split = kostyl(s, c);
	if (!(split))
		return (NULL);
	i = -1;
	j = 0;
	flag = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && flag < 0)
			flag = i;
		else if ((s[i] == c || i == ft_strlen(s)) && flag >= 0)
		{
			split[j] = word_str(s, flag, i);
			if (!(split[j++]))
				return (free_split(split));
			flag = -1;
		}
	}
	split[j] = 0;
	return (split);
}
