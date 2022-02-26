/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:41:21 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 21:41:23 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*len_bigger(char const *s, unsigned int start)
{
	char	*r;
	int		k;

	k = 0;
	r = (char *)malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	if (r == NULL)
		return (NULL);
	while (s[start])
		r[k++] = s[start++];
	r[k] = '\0';
	return (r);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*r;
	unsigned int		k;

	k = 0;
	if (!(s))
		return (NULL);
	if (start >= ft_strlen(s))
	{
		r = (char *)malloc(sizeof(char) * 1);
		r[0] = '\0';
		return (r);
	}
	if (len > ft_strlen(s + start))
		return (len_bigger(s, start));
	else
	{
		r = (char *)malloc(sizeof(char) * (len + 1));
		if (r == NULL)
			return (NULL);
		while (len--)
			r[k++] = s[start++];
		r[k] = '\0';
		return (r);
	}
	return (NULL);
}
