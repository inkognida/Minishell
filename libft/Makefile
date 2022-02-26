SRCS		=	ft_atoi.c ft_bzero.c ft_calloc.c \
				ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_itoa.c \
				ft_memchr.c ft_memcmp.c ft_memcpy.c \
				ft_memmove.c ft_memset.c ft_split.c \
				ft_strchr.c ft_strdup.c ft_strjoin.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c \
				ft_strtrim.c ft_substr.c ft_tolower.c \
				ft_toupper.c ft_putchar_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_putstr_fd.c ft_striteri.c \
				ft_strmapi.c

BONUS_SRCS	=	ft_lstnew.c  ft_lstadd_front.c \
				ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c	


OBJ_SRC = $(SRCS:.c=.o)

OBJ_BONUS = $(BONUS_SRCS:.c=.o)

NAME = libft.a

CC = gcc

REM = rm -f

LIBH = libft.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_SRC)
			ar rc $(NAME) $(OBJ_SRC)
			ranlib $(NAME)

%.o:	%.c $(LIBH)
			$(CC) $(FLAGS) -c $< -o $@

bonus: $(OBJ_SRC) $(OBJ_BONUS)
			ar rc $(NAME) $(OBJ_SRC) $(OBJ_BONUS)
			ranlib $(NAME)

clean:
	$(REM) $(OBJ_SRC) $(OBJ_BONUS) 

fclean: clean
	$(REM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re