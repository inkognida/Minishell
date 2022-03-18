/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:30:40 by hardella          #+#    #+#             */
/*   Updated: 2022/03/18 22:18:22 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_pipex(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;
	char	*r;

	i = 0;
	j = 0;
	k = -1;
	if (!(s1) || !(s2))
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	r = (char *)malloc(sizeof(char) * (i + j + 1));
	if (r == NULL)
		return (NULL);
	while (s1[++k])
		r[k] = s1[k];
	i = -1;
	while (s2[++i])
		r[k + i] = s2[i];
	r[k + i] = '\0';
	return (r);
}

int	ft_strncmp_pipex(char *s1, char *s2, int n)
{
	int				i;
	unsigned char	*r1;
	unsigned char	*r2;
	unsigned int	check;

	r1 = (unsigned char *) s1;
	r2 = (unsigned char *) s2;
	i = 0;
	while ((r1[i] || r2[i]) && i < n)
	{
		if (r1[i] != r2[i])
		{
			check = r1[i] - r2[i];
			return (check);
		}
		i++;
	}
	return (0);
}

char	*ft_strnstr_pipex(char *haystack, char *needle, int len)
{
	if (len == 0 && (ft_strlen_pipex(needle) != 0))
		return (NULL);
	if (ft_strlen_pipex(needle) == 0)
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (!ft_strncmp_pipex(haystack, needle, ft_strlen_pipex(needle)) && \
			len >= ft_strlen_pipex(needle))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
