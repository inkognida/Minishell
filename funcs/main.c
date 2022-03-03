/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/03/03 18:55:17 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_exit_status;

// int	valid_string(char *str)
// {
// 	char	*valid_str;
// 	int		i;

// 	i = 0;
// 	valid_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
// 	if (!valid_str)
// 		return (0);
// 	while (str[i])
// 	{
// 		while (str[i] != ' ' || str[i])
// 			valid_str[i] = str[i++];
// 		if (check_valid_cmd(valid_str) == 1)
// 		{
// 			i++;
// 			if ((int)str[i] == 39)
// 			{
// 				while ((int)str[++i] != 39)
// 					continue ;
// 				if (str[i] == '|' || str[i] == '')		
// 			}
// 		}
// 	}
// 	return (0);
// }

int	valid_string(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			sq++;
			while (str[i] != '\'' && str[i])
				i++;
			if (str[i] == '\'')
				sq++;
		}
		if (str[i] == '"')
		{
			i++;
			dq++;
			while (str[i] != '"' && str[i])
				i++;
			if (str[i] == '"')
				dq++;
		}
		if (str[i] == ';' || str[i] == '\\')
			return (0);
		i++;
	}
	if (sq % 2 == 0 && dq % 2 == 0)
		return (1);
	return (0);
}

int	launch_cmd(char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_execute(cmd, envp);
	else if (pid < 0)
   		ft_puterror();
	else
	{
		waitpid(pid, 0, WUNTRACED);
	}
	return (1);
}

void	handle_signal(int sig)
{
	g_exit_status += 2;
	if (sig == 2)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 3)
	{
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		exit (1);
	}
}

int	free_all(void)
{
	exit(1);
	return (1);
	//tmp func right now, need to add a lot
}

void	not_valid_string(void)
{
	write(2, "cmd line is not valid\n", ft_strlen("cmd line is not valid\n"));
	g_exit_status = 2;
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	// char	**split;

	(void)argc;
	(void)argv;
	//init env for what?
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = ft_strtrim(readline("minishell> "), " \t");
		add_history(str);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		if (str == NULL)
			return (free_all()); //need to free all
		if (valid_string(str) == 0)
			exit(1);
			// return (not_valid_string());
		// else
		if (ft_strlen(str) == 0)
			continue ;
		// split = parsing_str(str, envp);
		launch_cmd(str, envp);
		// free_line_all(&line, str);
	}
	return (0);
}
