#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include "./headers/minishell.h"


void	handle_signal(int sig)
{
	// g_exit_status += 2;
	if (sig == 2)
	{
		// g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 10);
		exit (1);
	}
}

void quotes(void)
{
	char str[10] = "abo'ba";
	int i = 0;
	while (str[i])
	{
		if ((int)str[i] == 39)
			printf("ABOBA");
		i++;
	}
}


int main(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	// // signal(EOF, handler);

	// while (1)
	// {
	// 	write(1, "a", 1);
	// 	sleep(1);
	// }

	char *str;

	str = readline("mini> ");
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	if (str == NULL)
	{
		printf("exit\n");
		exit(1);
	}

	// printf("%d\n", 4 % 2);

	quotes();
	return (0);
}