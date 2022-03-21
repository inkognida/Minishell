/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/03/21 15:02:19 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**split_args(char *str, char delim, int remove)
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
	if (remove)
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

void	launch_cmd(char **cmds, t_list **env)
{
	char	**files;
	int		input_flag;
	
	files = find_files(&cmds[arr_len(cmds) - 1], ">");
	create_files(files);
	input_flag = redirect_input(&(cmds[0]));
	if (input_flag == 1 && arr_len(cmds) == 1 && ft_strlen_free(ft_strtrim(cmds[0], " ")) == 0)
	{
		just_copy(files);
		return ;
	}
	if (input_flag == -1)
		return ;
	if (try_builtins(cmds, env) != -1)
		return ;
	if (arr_len(files) == 0)
	{
		if (input_flag)
		{
			close(0);
			open(".temp_input", O_RDONLY);
		}
		pipex(cmds, *env, NULL, 0);
	}
	redirect_output(cmds, files, *env, input_flag);
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


int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

char	*ft_strncat(char *dest, char *src, int nb)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (dest[i] != '\0')
		i++;
	while (j < nb)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_env_name(char *str, int i, t_list *env, int f)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char) * ft_lstsize(env));
	if (!tmp)
		return (NULL);
	while (!ft_isspace(str[i]) && str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '"' && str[i] != ':' && str[i] != '/')
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	// printf("%s\n", tmp);
	return (tmp);
}


char	*env_variables(char *str, t_list *env)
{
	int		i;
	int		f;
	char	*tmp;
	char	*env_tmp;

	i = 0;
	tmp = malloc(1);
	if (!tmp)
		return (NULL);
	f = 1;
	tmp[0] = '\0';
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '"')
		{
			tmp = ft_strjoin_free(tmp, "\"", 1, 0);
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == '$')
				{
					env_tmp = get_env_name(str, i + 1, env, f);
					if (env_find(env_tmp, env))
						tmp = ft_strjoin_free(tmp, env_find(env_tmp, env), 1, 0);
					i += ft_strlen(env_tmp);
					free(env_tmp);
					if (str[i] == '"')
					{
						i++;
						break ;
					}
				}
				else
					tmp = ft_strjoin_free(tmp, ft_substr(str, i, 1), 1, 1);
			}
			tmp = ft_strjoin_free(tmp, "\"", 1, 0);
		}
		else if (str[i] && str[i] == '\'')
		{
			tmp = ft_strjoin_free(tmp, "\'", 1, 0);
			while (str[++i] && str[i] != '\'')
				tmp = ft_strjoin_free(tmp, ft_substr(str, i, 1), 1, 1);
			tmp = ft_strjoin_free(tmp, "\'", 1, 0);
		}
		else if (str[i] == '$')
		{
			env_tmp = get_env_name(str, i + 1, env, f);
			if (env_find(env_tmp, env))
				tmp = ft_strjoin_free(tmp, env_find(env_tmp, env), 1, 0);
			i += ft_strlen(env_tmp);
			free(env_tmp);
		}
		else
			tmp = ft_strjoin_free(tmp, ft_substr(str, i, 1), 1, 1);
		i++;
	}
	return (tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*str;
	char	*stin_str;

	(void)argc;
	(void)argv;
	env = NULL;
	init_envp(&env, envp);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		stin_str = ttyname(STDIN_FILENO);
		str = ft_strtrim(readline("minishell> "), " \t");
		add_history(str);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		if (str == NULL)
			return (free_all()); //need to free all
		if (valid_string(str) == NULL)
		{
			printf("quote error\n");
			free(str);
			continue ;
		}
		if (ft_strlen(str) == 0)
			continue ;
		str = env_variables(str, env);
		launch_cmd(split_args(str, '|', 0), &env);
		dup2(open(stin_str, O_RDONLY), 0);
		free(str);
	}
	return (0);
}
