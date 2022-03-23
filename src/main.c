/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/03/23 12:14:23 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

//valid_string
char	*null_valid(char *valid_str, int j)
{
	valid_str[j] = '\0';
	return (valid_str);
}

int	continue_valid(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		return (1);
	}
	else if (str[*i] == '"')
		return (2);
	return (0);
}

char	*valid_helper(char *str, char *valid_str, int i, int j)
{
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'' && str[i])
				valid_str[j++] = str[i];
			if (continue_valid(str, &i) == 1 || continue_valid(str, &i) == 2)
				continue ;
			else if (str[i] == '\0')
				return (NULL);
		}
		if (str[i] == '"')
		{
			while (str[++i] != '"' && str[i])
				valid_str[j++] = str[i];
			if (str[i++] == '"')
				continue ;
			if (str[--i] == '\'')
				continue ;
			else if (str[i] == '\0')
				return (NULL);
		}
		valid_str[j++] = str[i++];
	}
	return (null_valid(valid_str, j));
}

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
	return (valid_helper(str, valid_str, i, j));
}
//valid_string

//split_args
void	split_args_helper(char *valid, char ***args, char delim)
{
	int	i;
	int	j;

	free(valid);
	i = -1;
	while ((*args)[++i])
	{
		j = -1;
		while ((*args)[i][++j])
			if ((*args)[i][j] == -1)
				(*args)[i][j] = delim;
	}
}

char	**split_args(char *str, char delim, int remove)
{
	char	*valid;
	char	**args;
	int		i;

	i = -1;
	valid = ft_strdup(str);
	if (valid == NULL)
		return (NULL);
	while (valid[++i])
	{
		if (valid[i] == '\'')
			while (valid[++i] != '\'' && valid[i])
				if (valid[i] == delim)
					valid[i] = -1;
		if (valid[i] == '"')
			while (valid[++i] != '"' && valid[i])
				if (valid[i] == delim)
					valid[i] = -1;
	}
	if (remove)
		valid = valid_string(valid);
	args = ft_split(valid, delim);
	split_args_helper(valid, &args, delim);
	return (args);
}
//split_args

//launch_cmd
void	launch_cmd_helper(void)
{
	close(0);
	open(".temp_input", O_RDONLY);
}

void	launch_cmd(char **cmds, t_list **env)
{
	char	**files;
	int		input_flag;

	files = find_files(&cmds[arr_len(cmds) - 1], ">");
	create_files(files);
	input_flag = redirect_input(&(cmds[0]));
	if (input_flag == 1 && arr_len(cmds) == 1 \
		&& ft_strlen_free(ft_strtrim(cmds[0], " ")) == 0)
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
			launch_cmd_helper();
		pipex(cmds, *env, NULL, 0);
	}
	redirect_output(cmds, files, *env, input_flag);
}
//launch_cmd

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
		exit(1);
	}
}

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

char	*ft_strncat(char *dest, char *src, int nb)
{
	int	i;
	int	j;

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

char	*update_exit(void)
{
	char	*num;

	num = ft_itoa(g_exit_status);
	if (!num)
		return (NULL);
	return (num);
}

char	*get_env_name(char *str, int i, t_list *env)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char) * ft_lstsize(env));
	if (!tmp)
		return (NULL);
	while (!ft_isspace(str[i]) && str[i] && str[i] != '$' && str[i] != '\'' \
			&& str[i] != '"' && str[i] != ':' && str[i] != '/')
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	env_variables_helper_one(char *tmps[2], char *str, int *i)
{
	tmps[0] = join_free(tmps[0], "\'", 1, 0);
	while (str[++(*i)] && str[(*i)] != '\'')
		tmps[0] = join_free(tmps[0], ft_substr(str, (*i), 1), 1, 1);
	tmps[0] = join_free(tmps[0], "\'", 1, 0);
}

void	env_variables_helper_two(char *tmps[2], char *str, int *i, t_list *env)
{
	tmps[1] = get_env_name(str, (*i) + 1, env);
	if (ft_strncmp(tmps[1], "?", ft_strlen("?") + 1) == 0)
		tmps[0] = join_free(tmps[0], update_exit(), 1, 0);
	else if (env_find(tmps[1], env))
		tmps[0] = join_free(tmps[0], env_find(tmps[1], env), 1, 0);
	(*i) += ft_strlen(tmps[1]);
	free(tmps[1]);
}

int	env_variables_help(char *str, int *i)
{
	if (str[*i] == '"')
	{
		*i += 1;
		return (1);
	}
	return (0);
}

void	ilya_spasibo_za_detstvo(char *tmps[2], int *i, char *str, t_list *env)
{
	if (str[*i] && str[*i] == '\'')
		env_variables_helper_one(tmps, str, i);
	else
		env_variables_helper_two(tmps, str, i, env);
}

void	loop_env_variables(char *tmps[2], char *str, int i, t_list *env)
{
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '"')
		{
			tmps[0] = join_free(tmps[0], "\"", 1, 0);
			while (str[++i] && str[i] != '"')
			{
				if (str[i] == '$')
				{	
					env_variables_helper_two(tmps, str, &i, env);
					if (env_variables_help(str, &i) == 1)
						break ;
				}
				else
					tmps[0] = join_free(tmps[0], ft_substr(str, i, 1), 1, 1);
			}
			tmps[0] = join_free(tmps[0], "\"", 1, 0);
		}
		else if ((str[i] && str[i] == '\'') || str[i] == '$')
			ilya_spasibo_za_detstvo(tmps, &i, str, env);
		else
			tmps[0] = join_free(tmps[0], ft_substr(str, i, 1), 1, 1);
		i++;
	}
}

char	*env_variables(char *str, t_list *env)
{
	int		i;
	char	*tmps[2];

	i = 0;
	tmps[0] = malloc(1);
	if (!tmps[0])
		return (NULL);
	tmps[0][0] = '\0';
	loop_env_variables(tmps, str, i, env);
	return (tmps[0]);
}

void	signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
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

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*str;
	char	*stin_str;

	(void)argc;
	(void)argv;
	env = NULL;
	g_exit_status = 0;
	init_envp(&env, envp);
	signals();
	while (1)
	{
		stin_str = ttyname(STDIN_FILENO);
		str = ft_strtrim(readline("minishell> "), " \t");
		if (str == NULL || stin_str == NULL)
			return (free_env(env));
		add_history(str);
		signals();
		if (invalid_str(str) == 0)
			continue ;
		if (ft_strlen(str) == 0)
			continue ;
		str = env_variables(str, env);
		launch_cmd(split_args(str, '|', 0), &env);
		dup2(open(stin_str, O_RDONLY), 0);
		free(str);
	}
	return (0);
}
