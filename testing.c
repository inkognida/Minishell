#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "./headers/minishell.h"

// int System(const char *cmd)
// {
// 	pid_t pid;
// 	int status;


// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);
// 	else if (pid == 0)
// 	{
// 		execl("/bin/sh", "sh", "-c", cmd, 0);
// 		perror("execl");
// 		exit(1);
// 	}
// 	if (waitpid(pid, &status, 0) == pid && WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (-1);
// }


// #define ft_close(fd) if (fd < -1) close(fd), fd=-1

int	arr_len(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
		i++;
	return (i);
}

void	ft_close(int fd)
{
	if (fd < -1)
		close(fd);
	fd = -1;
}

int main (int argc, char **cmds)
{
	int			fifo[2][2];
	int			cur_pipe;
	int			i;
	pid_t		pid;
	int			status;

	fifo[0][0] = -1;
	fifo[0][1] = -1;
	fifo[1][0] = -1;
	fifo[1][1] = -1;
	cur_pipe = 0;
	i = 1;
	while (i < argc)
	{
		if (pipe(fifo[cur_pipe]) == -1)
		{
			perror("pipe");
			exit(2);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(3);
		}
		if (pid == 0)
		{
			if (i > 1)
			{
				dup2(fifo[1 - cur_pipe][0], STDIN_FILENO);
				ft_close(fifo[1-cur_pipe][0]);
			}
			if (i < argc - 1)
			{
				dup2(fifo[cur_pipe][1], STDOUT_FILENO);
				ft_close(fifo[cur_pipe][0]);
				ft_close(fifo[cur_pipe][1]);
			}
			if (execl("/bin/sh", "sh", "-c", cmds[i], 0) == -1) // if (ft_execute(cmds[i], envp) == -1)
			{
				perror("execute");
				exit(5);
			}
		}
		ft_close(fifo[1 - cur_pipe][0]);
		ft_close(fifo[cur_pipe][1]);
		cur_pipe = 1 - cur_pipe;
		i++;
	}
	ft_close(fifo[1 - cur_pipe][0]);
	// while (i++ < argc)
	// 	waitpid(pid, &status, 0);
	// while// while(waitpid(pid, &status, 0) == pid && WIFEXITED(status));;
	while (waitpid(-1, 0, 0));
	return 0;
}

// #define CLOSE(fd) if (fd < -1) close(fd), fd=-1

// int main(int argc, char **argv)
// {
// 	int fifo[2][2];
// 	int cur_pipe = 0;
// 	fifo[0][0] = -1;
// 	fifo[0][1] = -1;
// 	fifo[1][0] = -1;
// 	fifo[1][1] = -1;
// 	for (int i = 1; i < argc; i++)
// 	{
// 		if (pipe(fifo[cur_pipe]))
// 		{
// 			perror("pipe");
// 			exit(2);
// 		}
// 		switch (fork())
// 		{
// 			case -1: perror("fork"), exit(3);
// 			case 0: if (i > 1)
// 					{
// 						dup2(fifo[1 - cur_pipe][0], STDIN_FILENO);
// 						CLOSE(fifo[1 - cur_pipe][0]);
// 					}
// 					if (i < argc - 1)
// 					{
// 						dup2(fifo[cur_pipe][1], STDOUT_FILENO);
// 						CLOSE(fifo[cur_pipe][0]);
// 						CLOSE(fifo[cur_pipe][1]);
// 					}
// 					if (execl("/bin/sh", "sh", "-c", argv[i], 0) == -1) // if (ft_execute(cmds[i], envp) == -1)
// 					{
// 						perror("execute");
// 						exit(5);
// 					}
// 			CLOSE(fifo[1 - cur_pipe][0]);
// 			CLOSE(fifo[cur_pipe][1]);
// 			cur_pipe = 1 - cur_pipe;
// 		}
// 	}
// 	CLOSE(fifo[1 - cur_pipe][0]);
// 	while (waitpid(pid, 0, 0));
// 	// while (waitpid(-1, 0, 0)) ;
// 	return (0);
// }

// int main(int argc, char **argv)

// int main(void)
// {
// 	int rc = 0;
// 	char buf[256];
// 	do
// 	{
// 		printf("sh> "); fflush(stdout);
// 		if (!(gets(buf))) break;
// 		rc = System(buf);
// 	} 	while (!rc);
// 	return (rc);
// }