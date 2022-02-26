/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:57:53 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 10:57:53 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
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
