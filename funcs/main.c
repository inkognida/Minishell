/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/03/04 20:55:48 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	g_exit_status;

char	*valid_string(char *str)
{
	char	*valid_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	valid_str = malloc(sizeof(char) * ft_strlen(str));
	if (valid_str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'' && str[i])
				valid_str[j++] = str[i];
			if (str[i] == '\'')
			{
				i++;
				continue ;
			}
			if (str[i] == '"')
				continue ;
			else if (str[i] == '\0')
				return (NULL);
		}
		if (str[i] == '"')
		{
			while (str[++i] != '"' && str[i])
				valid_str[j++] = str[i];
			if (str[i] == '"')
			{
				i++;
				continue ;
			}
			if (str[i] == '\'')
				continue ;
			else if (str[i] == '\0')
				return (NULL);
		}
		valid_str[j++] = str[i++];
	}
	valid_str[j] = '\0';
	return (valid_str);
}

char	**split_args(char *str)
{
	char	*valid;
	char	**args;
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			while (str[++i] != '\'' && str[i])
				if (str[i] == ' ')
					str[i] = -1;
		if (str[i] == '"')
		{
			while (str[++i] != '"' && str[i])
				if (str[i] == ' ')
					str[i] = -1;
		}
	}
	valid = valid_string(str);
	args = ft_split(valid, ' ');
	if (args == NULL)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			if (args[i][j] == -1)
				args[i][j] = ' ';
	}
	return (args);
}

int	launch_cmd(char **cmd, char **envp)
{
	pid_t	pid;

	if (cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			if (len_cmds(cmd) > 1)
				pipex(cmd, envp);
			else
				ft_execute(cmd[0], envp);
		}
		else if (pid < 0)
			ft_puterror();
		else
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

char	**parse(char *valid_str)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split(valid_str, '|');
	if (cmds == NULL)
		return (NULL);
	return (cmds);
}

// void	parsing_str(char *str)
// {

// }

//ft_execute("ls -l - a")
//pipex(["ls -l - a", "ls", "pwd"])
	// inside pipex (ft_execute("ls -l -a"))
	 // ft_execute("ls")
	 	// ft_execute("pwd")



int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	*valid;

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
		valid = valid_string(str);
		if (valid == NULL)
		{
			printf("quote error\n");
			free(str);
			continue ;
		}
		if (ft_strlen(str) == 0)
			continue ;
		launch_cmd(parse(str), envp);
	}
	return (0);
}
