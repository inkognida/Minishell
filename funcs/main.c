/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/03/07 17:13:06 by hardella         ###   ########.fr       */
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

char	**split_args(char *str, char delim)
{
	char	*valid;
	char	**args;
	int		i;
	int		j;

	i = -1;
	valid = ft_strdup(str);
	while (valid[++i])
	{
		if (valid[i] == '\'')
			while (valid[++i] != '\'' && valid[i])
				if (valid[i] == delim)
					valid[i] = -1;
		if (valid[i] == '"')
		{
			while (valid[++i] != '"' && valid[i])
				if (valid[i] == delim)
					valid[i] = -1;
		}
	}
	valid = valid_string(valid);
	args = ft_split(valid, delim);
	free(valid);
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			if (args[i][j] == -1)
				args[i][j] = delim;
	}
	return (args);
}

int	launch_cmd(char **cmd, t_list *envp)
{
	pid_t	pid;

	if (cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			pipex(cmd, envp);
			exit(0);
		}
		else if (pid < 0)
			ft_puterror();
		else
			waitpid(pid, 0, WUNTRACED);
	}
	return (1);
}


//func need to be done 
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


//display functions

void display(t_list *env)
{
	while (env->next)
	{
		if (ft_strncmp(env->content, "PWD", 3) == 0)
			printf("%s\n", env->content);
		else if (ft_strncmp(env->content, "OLDPWD", 6) == 0)
			printf("%s\n", env->content);
		env = env->next;
	}
}

void display_arr(char **envp)
{
	int i = 0;
	int j;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			printf("%c", envp[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// display functions

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
		strs[i] = (char *)lst->content;
		lst = lst->next;
		i++;
	}
	return (strs);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*str;
	char	*valid;

	// char **back_env;

	(void)argc;
	(void)argv;
	env = NULL;
	init_envp(&env, envp);
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
		launch_cmd(parse(str), env);
	}
	return (0);
}
