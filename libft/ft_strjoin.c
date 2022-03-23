/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:57:34 by hardella          #+#    #+#             */
/*   Updated: 2022/03/22 13:38:25 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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

char	*ft_strjoin_free(char *s1, char *s2, int f1, int f2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (res);
}

char	*join_free(char *s1, char *s2, int f1, int f2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (res);
}
