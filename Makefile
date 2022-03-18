SRCS	=	./src/main.c ./src/redirect.c ./src/utils.c\
			./get_next_line/gnl_utils.c ./get_next_line/gnl.c \
			./src/ft_split_pipex.c ./src/pipex.c ./src/pipex_funcs.c ./src/pipex_utils.c \
			./src/env.c ./src/builtins.c ./src/errors.c\


OBJ_SRC = 	${SRCS:.c=.o}

CC 		= 	gcc

NAME = minishell

REM = rm -f

HEADER = ./src/minishell.h

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