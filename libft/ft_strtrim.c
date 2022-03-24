/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:58:08 by hardella          #+#    #+#             */
/*   Updated: 2022/03/23 22:04:16 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_arr(char const *arr, char c)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen(arr))
		if (arr[i] == c)
			return (1);
	return (0);
}

static int	count_to_trim(char const *s1, char const *set)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (in_arr(set, s1[i]) && i < ft_strlen(s1))
		i++;
	count = i;
	if (i == ft_strlen(s1))
		return (count);
	i = ft_strlen(s1);
	while (in_arr(set, s1[--i]))
		count++;
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	count;

	if (s1 == NULL || set == NULL)
		return (NULL);
	res = malloc(ft_strlen(s1) - count_to_trim(s1, set) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (in_arr(set, s1[i]))
		i++;
	count = i;
	while (i < ft_strlen(s1) - (count_to_trim(s1, set) - count))
		*res++ = s1[i++];
	*res = '\0';
	res -= (ft_strlen(s1) - count_to_trim(s1, set));
	return (res);
}

char	*ft_strtrim_free(char *s1, char *set)
{
	char	*res;

	res = ft_strtrim(s1, set);
	free(s1);
	return (res);
}
