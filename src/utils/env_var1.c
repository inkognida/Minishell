/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:10:44 by hardella          #+#    #+#             */
/*   Updated: 2022/03/24 18:41:02 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

void	loop_env_variables(char *tmps[2], char *str, int i, t_list *env)
{
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '"')
		{
			tmps[0] = join_free(tmps[0], "\"", 1, 0);
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == '$')
				{	
					env_variables_helper_two(tmps, str, &i, env);
					if (env_variables_help(str, &i) == 1)
						break ;
				}
				else
					tmps[0] = join_free(tmps[0], ft_substr(str, i, 1), 1, 1);
			}
			tmps[0] = join_free(tmps[0], "\"", 1, 0);
		}
		else if ((str[i] && str[i] == '\'') || str[i] == '$')
			ilya_spasibo_za_detstvo(tmps, &i, str, env);
		else
			tmps[0] = join_free(tmps[0], ft_substr(str, i, 1), 1, 1);
		i++;
	}
}

char	*env_variables(char *str, t_list *env)
{
	int		i;
	char	*tmps[2];

	i = 0;
	tmps[0] = malloc(1);
	if (!tmps[0])
		return (NULL);
	tmps[0][0] = '\0';
	loop_env_variables(tmps, str, i, env);
	free(str);
	return (tmps[0]);
}

char	*update_exit(void)
{
	char	*num;

	num = ft_itoa(g_exit_status);
	if (!num)
		return (NULL);
	return (num);
}

char	*ft_strncat(char *dest, char *src, int nb)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (dest[i] != '\0')
		i++;
	while (j < nb)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
