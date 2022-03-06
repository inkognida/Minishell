SRCS	=	./funcs/main.c ./funcs/redirect.c ./funcs/utils.c ./get_next_line/gnl_utils.c ./get_next_line/gnl.c ./pipex/errors_pipex.c \
			./pipex/ft_split_pipex.c ./pipex/pipex.c ./pipex/pipex_funcs.c ./pipex/pipex_utils.c \
			./funcs/init_envp.c ./pipex/own_commands.c \


OBJ_SRC = 	${SRCS:.c=.o}

CC 		= 	gcc

NAME = minishell

REM = rm -f

HEADER = ./headers/minishell.h

FLAGS = -Wall -Wextra -g #Werror need to be added   -Werror 

readline = ./readline/libhistory.a ./readline/libreadline.a

.PHONY: all clean fclean re

%.o:	%.c ${HEADER}
			${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ_SRC}
			make -C ./libft/
			${CC} ${FLAGS} ${OBJ_SRC} ./libft/libft.a $(readline) -ltermcap -o ${NAME}

all: ${NAME}

clean:
	make clean -C ./libft/
	${REM} ${OBJ_SRC}

fclean: clean
	make fclean -C ./libft/
	${REM} ${OBJ_SRC} ${NAME}

re: fclean all