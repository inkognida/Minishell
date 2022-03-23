/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:12:35 by hardella          #+#    #+#             */
/*   Updated: 2022/03/23 16:14:21 by hardella         ###   ########.fr       */
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
	if (valid_string(str) == NULL)
	{
		printf("quote error\n");
		g_exit_status = 127;
		free(str);
		return (0);
	}
	return (1);
}

void	signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
