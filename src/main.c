/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hardella <hardella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:13:07 by hardella          #+#    #+#             */
/*   Updated: 2022/03/25 16:48:56 by hardella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	launch_cmd_helper(void)
{
	close(0);
	open(".temp_input", O_RDONLY);
}

int	free_arrs(char **arr1, char **arr2, int f1, int f2)
{
	if (f1)
		free_arr(arr1);
	if (f2)
		free_arr(arr2);
	return (1);
}

int	launch_cmd(char **cmds, t_list **env)
{
	char	**files;
	int		input_flag;

	g_exit_status = 0;
	files = find_files(&cmds[arr_len(cmds) - 1], ">");
	create_files(files);
	input_flag = redirect_input(&(cmds[0]));
	if (input_flag == 1 && arr_len(cmds) == 1 \
		&& ft_strlen_free(ft_strtrim(cmds[0], " ")) == 0)
		return (just_copy(files, cmds));
	if (input_flag == -1)
		return (free_arrs(files, cmds, 1, 1));
	if (try_builtins(cmds, env) != -1)
		return (free_arrs(files, cmds, 1, 1));
	if (arr_len(files) == 0)
	{
		if (input_flag)
			launch_cmd_helper();
		pipex(cmds, *env, NULL, 0);
	}
	redirect_output(cmds, files, *env, input_flag);
	return (free_arrs(files, cmds, 1, 1));
}

void	handle_signal(int sig)
{
	g_exit_status += 2;
	if (sig == 2)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 3)
	{
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		exit(1);
	}
}

int	cycle(char *stdin_str, char *str, t_list *env)
{
	while (1)
	{
		stdin_str = ttyname(STDIN_FILENO);
		str = ft_strtrim_free(readline("minishell> "), " \t");
		if (str == NULL || stdin_str == NULL)
			return (free_env(env));
		if (ft_strlen(str))
			add_history(str);
		signals();
		if (invalid_str(str) == 0)
			continue ;
		if (ft_strlen(str) == 0)
		{
			free(str);
			continue ;
		}
		str = env_variables(str, env);
		launch_cmd(split_args(str, '|', 0), &env);
		dup2(open(stdin_str, O_RDONLY), 0);
		free(str);
	}
	ft_lstclear(&env, free);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env;
	char	*str;
	char	*stdin_str;

	(void)argc;
	(void)argv;
	env = NULL;
	init_envp(&env, envp);
	signals();
	g_exit_status = 0;
	str = NULL;
	stdin_str = NULL;
	cycle(stdin_str, str, env);
	return (0);
}
