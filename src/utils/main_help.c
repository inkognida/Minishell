/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:12:35 by hardella          #+#    #+#             */
/*   Updated: 2022/03/23 22:06:09 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

int	free_env(t_list *env)
{
	free(env);
	g_exit_status = 1;
	return (g_exit_status);
}

void	not_valid_string(void)
{
	write(2, "cmd line is not valid\n", ft_strlen("cmd line is not valid\n"));
	exit(1);
}

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	invalid_str(char *str)
{
	char	*valid;

	valid = valid_string(str);
	if (valid == NULL)
	{
		printf("quote error\n");
		g_exit_status = 127;
		free(str);
		free(valid);
		return (0);
	}
	free(valid);
	return (1);
}

void	signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
