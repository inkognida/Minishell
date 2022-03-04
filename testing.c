// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <stdlib.h>
// #include <signal.h>
// #include "./headers/minishell.h"


// void	handle_signal(int sig)
// {
// 	// g_exit_status += 2;
// 	if (sig == 2)
// 	{
// 		// g_exit_status = 130;
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	if (sig == SIGQUIT)
// 	{
// 		write(2, "Quit (core dumped)\n", 10);
// 		exit (1);
// 	}
// }

// void quotes(void)
// {
// 	char str[10] = "abo'ba";
// 	int i = 0;
// 	while (str[i])
// 	{
// 		if ((int)str[i] == 39)
// 			printf("ABOBA");
// 		i++;
// 	}
// }


// char	**parse(char *valid_str)
// {
// 	char	**cmds;
// 	int		i;

// 	i = 0;
// 	cmds = ft_split(valid_str, '|');
// 	if (cmds == NULL)
// 		return (NULL);
// 	while (cmds[i])
// 		printf("%s\n", cmds[i++]);
// 	return (cmds);
// }


// int main(void)
// {
// 	signal(SIGINT, handle_signal);
// 	signal(SIGQUIT, SIG_IGN);
// 	// // signal(EOF, handler);

// 	// while (1)
// 	// {
// 	// 	write(1, "a", 1);
// 	// 	sleep(1);
// 	// }

// 	char *str;

// 	str = readline("mini> ");
// 	signal(SIGINT, handle_signal);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (str == NULL)
// 	{
// 		printf("exit\n");
// 		exit(1);
// 	}

// 	// printf("%d\n", 4 % 2);

// 	quotes();

	

// 	return (0);
// }


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(int agrc, char* agrv[])
{
  int pipefds[2];
    pid_t pid;
  if(pipe(pipefds) == -1){
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  pid = fork();
  if(pid == -1){
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if(pid == 0){
  //replace stdout with the write end of the pipe
    dup2(pipefds[1],STDOUT_FILENO);  
  //close read to pipe, in child    
    close(pipefds[0]);               
    execlp("ls","ls",NULL);
    exit(EXIT_SUCCESS);
  }else{
  //Replace stdin with the read end of the pipe
        dup2(pipefds[0],STDIN_FILENO);  
  //close write to pipe, in parent
        close(pipefds[1]);               
        execlp("less","less",NULL);
        exit(EXIT_SUCCESS);
    }   
}


