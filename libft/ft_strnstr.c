/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:57:56 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 10:58:00 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (len == 0 && (ft_strlen(needle) != 0))
		return (NULL);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (!ft_strncmp(haystack, needle, ft_strlen(needle)) && \
			len >= ft_strlen(needle))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
