/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/02/26 19:47:15 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "ls", ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

char	**parsing_str(char *str, char **envp)
{
	char	**split;

	split = ft_split(str, ' ');
	if (check_cmd(split[0]))
		ft_execute(split[0], envp);
	else
		return (NULL);
	return (split);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**split;
	int		status;

	(void)argc;
	(void)argv;
	status = 1;
	while (status)
	{
		ft_putstr_fd("minishell> ", 1);
		str = get_next_line(0);
		split = parsing_str(str, envp);
		status = 0;
	}
	return (0);
}
