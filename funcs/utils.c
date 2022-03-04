/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:17:00 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/04 20:17:12 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*trim_free(char *str, char *charset)
{
	char	*trimmed;

	trimmed = ft_strtrim(str, charset);
	free(str);
	return (trimmed);
}
