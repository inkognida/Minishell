/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:11:30 by hardella          #+#    #+#             */
/*   Updated: 2022/03/25 10:11:04 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_name(char *str, int i, t_list *env)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char) * ft_lstsize(env));
	if (!tmp)
		return (NULL);
	while (!ft_isspace(str[i]) && str[i] && str[i] != '$' && str[i] != '\'' \
			&& str[i] != '"' && str[i] != ':' && str[i] != '/')
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	env_variables_helper_one(char *tmps[2], char *str, int *i)
{
	tmps[0] = join_free(tmps[0], "\'", 1, 0);
	while (str[++(*i)] && str[(*i)] != '\'')
		tmps[0] = join_free(tmps[0], ft_substr(str, (*i), 1), 1, 1);
	tmps[0] = join_free(tmps[0], "\'", 1, 0);
}

void	env_variables_helper_two(char *tmps[2], char *str, int *i, t_list *env)
{
	char	*tmp;

	tmps[1] = get_env_name(str, (*i) + 1, env);
	if (ft_strncmp(tmps[1], "?", ft_strlen("?") + 1) == 0)
	{
		tmp = update_exit();
		tmps[0] = join_free(tmps[0], tmp, 1, 0);
		free(tmp);
	}
	else if (env_find(tmps[1], env))
		tmps[0] = join_free(tmps[0], env_find(tmps[1], env), 1, 0);
	(*i) += ft_strlen(tmps[1]);
	free(tmps[1]);
}

int	env_variables_help(char *str, int *i)
{
	if (str[*i] == '"')
	{
		*i += 1;
		return (1);
	}
	return (0);
}

void	ilya_spasibo_za_detstvo(char *tmps[2], int *i, char *str, t_list *env)
{
	if (str[*i] && str[*i] == '\'')
		env_variables_helper_one(tmps, str, i);
	else
		env_variables_helper_two(tmps, str, i, env);
}
