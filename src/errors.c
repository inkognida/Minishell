/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:20:59 by hardella          #+#    #+#             */
/*   Updated: 2022/03/18 22:10:15 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_puterror(void)
{
	perror("Error");
	exit(1);
}

void	ft_putmallocerror(char *str)
{
	perror("Error");
	free(str);
	exit(1);
}

void	ft_bonuserror(void)
{
	perror("Error");
	exit(1);
}

int	ft_error(char *from, char *message, int exit_flag)
{
	int	should_exit;

	if (exit_flag < 0)
	{
		should_exit = 0;
		exit_flag *= -1;
	}
	else
		should_exit = 1;
	ft_putstr_fd(from, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (should_exit)
		exit(exit_flag);
	return (exit_flag);
}

int	ft_error_file(char *from, char *file, char *message, int exit_flag)
{
	int	should_exit;

	if (exit_flag < 0)
	{
		should_exit = 0;
		exit_flag *= -1;
	}
	else
		should_exit = 1;
	ft_putstr_fd(from, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (should_exit)
		exit(exit_flag);
	return (exit_flag);
}
