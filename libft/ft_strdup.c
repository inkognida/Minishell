/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:57:27 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 10:57:27 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		i;
	int		g;

	i = 0;
	g = 0;
	while (src[i])
		i++;
	copy = (char *) malloc(sizeof(char) * (i + 1));
	if (copy == NULL)
		return (NULL);
	while (src[g])
	{
		copy[g] = src[g];
		g++;
	}
	copy[g] = '\0';
	return (copy);
}
