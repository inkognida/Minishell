/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:55:54 by hardella          #+#    #+#             */
/*   Updated: 2021/10/13 10:55:55 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*itoa_pos(int n, int n_copy)
{
	int		end;
	int		count;
	char	*r;

	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	end = count;
	r = (char *)malloc(sizeof(char) * (count + 1));
	if (r == NULL)
		return (NULL);
	while (count-- > 0)
	{
		r[count] = (char)(n_copy % 10 + '0');
		n_copy /= 10;
	}
	r[end] = '\0';
	return (r);
}

static char	*itoa_neg(int n, int n_copy)
{
	int		end;
	int		count;
	char	*r;

	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	end = count + 1;
	r = (char *)malloc(sizeof(char) * (count + 2));
	if (r == NULL)
		return (NULL);
	r[0] = '-';
	count++;
	while (count-- > 1)
	{
		r[count] = (char)(n_copy % 10 + '0');
		n_copy /= 10;
	}
	r[end] = '\0';
	return (r);
}

static char	*itoa_min(int n, int n_copy)
{
	int		end;
	int		count;
	char	*r;

	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	end = count + 1;
	r = (char *)malloc(sizeof(char) * (count++ + 2));
	if (r == NULL)
		return (NULL);
	r[0] = '-';
	while (count-- > 1)
	{
		if (count == 10)
			r[count] = (char)((n_copy % 10 + 1) + '0');
		else
			r[count] = (char)(n_copy % 10 + '0');
		n_copy /= 10;
	}
	r[end] = '\0';
	return (r);
}

char	*ft_itoa(int n)
{
	char	*r;

	if (n > 0)
	{
		r = itoa_pos(n, n);
		return (r);
	}
	else if (n == -2147483648)
	{
		r = itoa_min(-n, -n - 1);
		return (r);
	}
	else if (n < 0)
	{
		r = itoa_neg(-n, -n);
		return (r);
	}
	else if (n == 0)
	{
		r = (char *)malloc(sizeof(char) * (2));
		r[0] = '0';
		r[1] = '\0';
		return (r);
	}
	return (NULL);
}
