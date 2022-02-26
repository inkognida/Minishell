/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:58:04 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 10:58:04 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	temp;

	i = 0;
	temp = c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == temp)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
