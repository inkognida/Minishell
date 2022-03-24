/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:17:31 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/24 17:55:18 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(char **arr)
{
	int		i;
	char	*val;

	i = -1;
	while (arr[++i])
	{
		val = ft_strchr(arr[i], '=');
		write(1, arr[i], ft_strlen(arr[i]) - ft_strlen(val));
		if (ft_strchr(val + 1, '=') || ft_strlen(val) == 1)
			printf("='%s'\n", val + 1);
		else
			printf("%s\n", val);
	}
	free_arr(arr);
}

int	ft_export_show(t_list *env)
{
	char	**arr;
	char	*temp;
	int		i;
	int		j;

	arr = convert_list_to_arr(env);
	i = 0;
	while (i < arr_len(arr) - 1)
	{
		j = i + 1;
		while (j < arr_len(arr))
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
	print_env(arr);
	return (0);
}

int	mini_export(char **args, char **k_v, int i, t_list **env)
{
	t_list	*new;

	if (ft_strncmp(args[i], "=", 2) == 0)
		return (ft_error("minishell", "bad assignment", -1));
	if (ft_strrchr(args[i], '=') == NULL)
		args[i] = ft_strjoin_free(args[i], "=", 1, 0);
	if (args[i][0] == '=')
		return (ft_error_file("minishell", args[i] + 1, "not found", -1));
	k_v = ft_split(args[i], '=');
	if (ft_isdigit(args[i][0]))
		return (ft_error_export_free("export", "not an identifier", k_v));
	if (env_find(k_v[0], *env))
		env_edit(k_v[0], args[i] + ft_strlen(k_v[0]) + 1, env);
	else
	{
		new = ft_lstnew(ft_strdup(args[i]));
		if (new == NULL)
			ft_error("export", "malloc error", -1);
		ft_lstadd_back(env, new);
	}
	free_arr(k_v);
	return (0);
}

int	ft_export(char **args, t_list **env)
{
	int		i;
	char	**k_v;

	k_v = NULL;
	if (args[1] == NULL)
		return (ft_export_show(*env));
	i = 0;
	while (args[++i])
		mini_export(args, k_v, i, env);
	free_arr(args);
	return (0);
}

int	ft_unset(char **args, t_list **env)
{
	int	i;

	if (args[1] == NULL)
		ft_error("unset", "not enough arguments", -1);
	i = 0;
	while (args[++i])
		env_remove(args[i], env);
	free_arr(args);
	return (0);
}
