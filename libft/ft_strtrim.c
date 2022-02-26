/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:58:08 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 10:58:08 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_char(char c, char const *b)
{
	int	i;

	i = 0;
	while (b[i])
	{
		if (c == b[i])
			return (1);
		i++;
	}
	return (0);
}

static int	f_pos(char const *s, char const *set)
{
	int	i;

	i = 0;
	while (check_char(s[i], set) == 1 && s[i])
		i++;
	return (i);
}

static int	l_pos(char const *s, char const *set)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
		i++;
	i--;
	while (check_char(s[i], set) == 1 && s[j])
	{
		j++;
		i--;
	}
	return (i);
}

static char	*cut_strtrim(char const *s1, char const *set)
{
	char	*r;
	int		i;
	int		f_s;
	int		l_s;

	i = 0;
	l_s = l_pos(s1, set);
	f_s = f_pos(s1, set);
	if (l_s == f_s)
	{
		r = (char *)malloc(sizeof(char) * 2);
		r[i] = s1[l_s];
		r[++i] = '\0';
		return (r);
	}
	r = (char *)malloc(sizeof(char) * (l_pos(s1, set) - f_pos(s1, set) + 2));
	if (r == NULL)
		return (NULL);
	while (i < (l_pos(s1, set) - f_pos(s1, set) + 1))
	{
		r[i++] = s1[f_s];
		f_s++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char				*r;
	int					i;
	int					j;
	unsigned int		c;

	if (!(s1) || !(set))
		return (NULL);
	i = -1;
	c = 0;
	while (s1[++i])
	{
		j = -1;
		while (set[++j])
			if (set[j] == s1[i])
				c++;
	}
	if (c == ft_strlen(s1))
	{
		r = (char *)malloc(sizeof(char) * 1);
		r[0] = '\0';
		return (r);
	}
	r = cut_strtrim(s1, set);
	return (r);
}
