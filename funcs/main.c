/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/03/03 19:48:19 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


int	g_exit_status;

int	valid_string(char *str)
{
	char	*valid_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	valid_str = malloc(sizeof(char) * ft_strlen(str));
	if (valid_str == NULL)
		return (1); //error
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				valid_str[j++] = str[i++];
			if (str[i] == '\'')
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
				valid_str[j++] = str[i++];
			if (str[i] == '"')
				i++;
		}
		valid_str[j] = str[i];
		i++;
		j++;
	}
	valid_str[j] = '\0';
	printf("%s\n", valid_str);
	return (1);
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

void	cut_cmd(char **split)
{
	exit(1);
}

// void	parsing_str(char *str)
// {
// 	char **cmds;

// 	cmds = ft_split(str, ' ');
// 	if (cmds == NULL)
// 		return ; //need to free all
	
	
// }


int	main(int argc, char **argv, char **envp)
{
	char	*str;

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
			printf("wrong\n");
		//parse_string(str); //probably need to add structure with cmds
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
