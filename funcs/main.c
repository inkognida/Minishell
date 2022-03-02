/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/03/02 18:55:25 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"



int	g_exit_status;

int	check_valid_cmd(char *valid_str)
{
	if (ft_strncmp(valid_str, "echo", ft_strlen(valid_str)) == 0)
		return (1);
	if (ft_strncmp(valid_str, "cd", ft_strlen(valid_str)) == 0)
		return (1);
	if (ft_strncmp(valid_str, "pwd", ft_strlen(valid_str)) == 0)
		return (1);
	if (ft_strncmp(valid_str, "export", ft_strlen(valid_str)) == 0)
		return (1);
	if (ft_strncmp(valid_str, "unset", ft_strlen(valid_str)) == 0)
		return (1);
	if (ft_strncmp(valid_str, "env", ft_strlen(valid_str)) == 0)
		return (1);
	if (ft_strncmp(valid_str, "exit", ft_strlen(valid_str)) == 0)
		return (1);
}

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


int	valid_string(char *str) //govno iz zhopi
{
	int	j;
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			single_quote++;
			while (str[i] != '\'' && str[i])
				i++;
			single_quote++;	
		}
		i++;
	}
	while (str[i])
	{
		if (str[i] == '"')
		{
			double_quote++;
			while (str[i] != '"' && str[i])
				i++;
			double_quote++;	
		}
		i++;
	}
	if (single_quote % 2 == 0 && double_quote % 2 == 0)
		return (1);
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
	char	**split;

	(void)argc;
	(void)argv;
	//init env for what?
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		if (str == NULL)
			return (free_all()); //need to free all
		printf("wrong string input %d\n", valid_string(str));
		if (valid_string(str) == 0)
			exit(1);
			// return (not_valid_string());
		// else
		// 	exec_cmd(&line, str);
		// free_line_all(&line, str);
	}
	return (0);
}
