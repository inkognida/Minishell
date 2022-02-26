/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:56:50 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 10:56:50 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	*r_dest;
	unsigned char	*r_source;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dest == source)
		return (dst);
	if (dest < source)
	{
		while (len--)
			*dest++ = *source++;
	}
	else
	{
		r_dest = (unsigned char *)(dst + (len - 1));
		r_source = (unsigned char *)(src + (len - 1));
		while (len--)
			*r_dest-- = *r_source--;
	}
	return (dst);
}
