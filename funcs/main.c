/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/02/27 20:00:27 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	str_check(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|')
			dif = 1;
		if (str[i] == '|')
		{
			if (dif == 0)
				return (1);
			dif = 0;
		}
		i++;
	}
	return (0);
}

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

	(void)argc;
	(void)argv;
	//handle env (malloc include)
	//need to handle signals
	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		//need to handle signals
		if (str == 0)
			return (free_all()); //need to free all
		if (str_check(str) == 0)
			return (error_str()); //some wrong str
		else
			exec_cmd(&line, str); //line is struct for input
		// split = parsing_str(str, envp);
		free_line_all(&line, str);
	}
	return (0);
}
