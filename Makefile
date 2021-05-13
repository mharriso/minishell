NAME	=	minishell
SRC		=	src
EX_FUNC =	ex_func
LIB		=	lib
INC		=	inc

HEADER	=	ex_func.h \
			exit.h \
			ftlib.h \
			env_func.h

HFILES	=	$(addprefix $(INC)/, $(HEADER))

SOURCE =	${EX_FUNC}/ft_pwd.c \
			${EX_FUNC}/ft_cd.c \
			${EX_FUNC}/ft_env.c \
			${EX_FUNC}/ft_export.c \
			${EX_FUNC}/ft_exit.c \
			${EX_FUNC}/env_func.c \
			${LIB}/ft_strlen.c \
			${LIB}/ft_strdup.c \
			${LIB}/ft_isalnum.c \
			${LIB}/ft_isalpha.c \
			${LIB}/ft_isdigit.c \
			${LIB}/ft_strcmp.c \
			exit.c \
			minishell.c

FLAGS	= -Wall -Wextra -Werror

OBJECTS	= ${SOURCE:.c=.o}

all: ${NAME}

$(NAME): ${OBJECTS}
	gcc -I ${INC} $(OBJECTS) -o $(NAME)

%.o: %.c ${HFILES}
	gcc ${FLAGS} -I ${INC} -c $< -o $@

clean:
	rm -f ${OBJECTS}
fclean: clean
	rm -f ${NAME}
re: fclean all

norm:
	norminette ex_func/*

.PHONY: all clean fclean re

