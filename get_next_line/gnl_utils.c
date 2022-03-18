/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:57:34 by hardella          #+#    #+#             */
/*   Updated: 2022/03/18 22:19:23 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
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
	free(s1);
	return (r);
}

void	*ft_memcpy_gnl(void *dst, void *src, int n)
{
	char	*dest;
	char	*source;

	if (!(dst) && !(src))
		return (NULL);
	dest = (char *)dst;
	source = (char *)src;
	while (n > 0)
	{
		*dest = *source;
		dest++;
		source++;
		n--;
	}
	return (dst);
}

int	ft_strlcpy_gnl(char *dst, char *src, int dstsize)
{
	int	srcm;

	srcm = ft_strlen_gnl(src);
	if (srcm + 1 < dstsize)
		ft_memcpy_gnl(dst, src, srcm + 1);
	else if (dstsize != 0)
	{
		ft_memcpy_gnl(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srcm);
}

char	*ft_strchr_gnl(char *s, int c)
{
	char	temp;

	temp = c;
	if (c == '\0')
		return ((char *)(s + ft_strlen_gnl(s)));
	while (*s)
	{
		if (*s == temp)
			return ((char *)s);
		s++;
		if (*s == '\0')
			return (NULL);
	}
	return (NULL);
}

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
