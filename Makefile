SRCS    =    ./src/main.c ./src/utils/utils.c ./src/utils/env.c ./src/utils/errors.c \
            ./src/redirect/redirect_input.c ./src/redirect/redirect_output.c \
            ./get_next_line/gnl_utils.c ./get_next_line/gnl.c \
            ./src/ft_split_pipex.c ./src/pipex.c ./src/pipex_funcs.c ./src/pipex_utils.c \
            ./src/builtins/builtins.c ./src/builtins/builtins_export.c ./src/builtins/builtins_path.c \
            ./src/utils/args_split.c ./src/utils/valid.c ./src/utils/env_var1.c ./src/utils/env_var2.c \
            ./src/utils/main_help.c ./src/redirect/redirect_help.c

OBJ_SRC = 	${SRCS:.c=.o}

CC 		= 	gcc

NAME = minishell

REM = rm -f

HEADER = ./src/minishell.h

FLAGS = -Wall -Wextra -Werror -g

readline = ./readline/libhistory.a ./readline/libreadline.a

.PHONY: all clean fclean re

%.o:	%.c ${HEADER}
			${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ_SRC}
			make -C ./libft/
			${CC} ${FLAGS} ${OBJ_SRC} ./libft/libft.a $(readline) -ltermcap -o ${NAME} -lreadline

all: ${NAME}

clean:
	make clean -C ./libft/
	${REM} ${OBJ_SRC}

fclean: clean
	make fclean -C ./libft/
	${REM} ${OBJ_SRC} ${NAME}

re:         fclean all
