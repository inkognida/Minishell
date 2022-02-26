/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:57:49 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 10:57:49 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	j;
	char			*dest;

	if (!(s) || !(f))
		return (NULL);
	j = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!(s) || !(dest))
		return (NULL);
	while (j < ft_strlen(s))
	{
		dest[j] = f(j, s[j]);
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
