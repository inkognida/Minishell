/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:06:18 by hardella          #+#    #+#             */
/*   Updated: 2022/03/25 20:16:53 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_envp(t_list **env, char **envp)
{
	int		i;
	char	*tmp;
	t_list	*env_tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_strdup(envp[i]);
		if (tmp == NULL)
			exit(1);
		env_tmp = ft_lstnew(tmp);
		if (env_tmp == NULL)
			exit(1);
		ft_lstadd_back(env, env_tmp);
		i++;
	}
}

char	**convert_list_to_arr(t_list *lst)
{
	char	**strs;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(lst);
	strs = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		strs[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	return (strs);
}

char	*env_find(char *key, t_list *env)
{
	while (env)
	{
		if (ft_strncmp(key, env->content, ft_strlen(key)) == 0 \
		&& ((char *)env->content)[ft_strlen(key)] == '=')
			return ((env->content) + ft_strlen(key) + 1);
		env = env->next;
	}
	return (NULL);
}

void	env_edit(char *key, char *value, t_list **env)
{
	t_list	*curr;
	char	*new;
	int		new_len;

	curr = *env;
	while (*env)
	{
		if (ft_strncmp(key, (*env)->content, ft_strlen(key)) == 0 \
		&& ((char *)(*env)->content)[ft_strlen(key)] == '=')
		{
			new_len = ft_strlen(key) + ft_strlen(value) + 2;
			new = malloc(new_len);
			new[0] = 0;
			ft_strlcat(new, key, new_len);
			ft_strlcat(new, "=", new_len);
			ft_strlcat(new, value, new_len);
			ft_strlcat(new, "\0", new_len);
			free((*env)->content);
			(*env)->content = new;
		}
		(*env) = (*env)->next;
	}
	(*env) = curr;
}

void	env_remove(char *key, t_list **env)
{
	t_list	*curr;
	t_list	*prev;

	curr = *env;
	prev = NULL;
	while (*env)
	{
		if (ft_strncmp(key, (*env)->content, ft_strlen(key)) == 0 \
		&& ((char *)(*env)->content)[ft_strlen(key)] == '=')
		{
			if (prev == NULL)
			{
				prev = (*env)->next;
				ft_lstdelone(*env, free);
				*env = prev;
				return ;
			}
			prev->next = (*env)->next;
			ft_lstdelone(*env, free);
			break ;
		}
		prev = *env;
		(*env) = (*env)->next;
	}
	(*env) = curr;
}
