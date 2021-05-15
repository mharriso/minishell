NAME	=	minishell
SRC		=	src
EX_FUNC =	ex_func
FT		=	libft
INC		=	inc

HEADER	=	ex_func.h \
			exit.h \
			env_func.h\
			libft.h

HFILES	=	$(addprefix $(INC)/, $(HEADER))

SOURCES	=	${EX_FUNC}/ft_pwd.c \
			${EX_FUNC}/ft_cd.c \
			${EX_FUNC}/ft_env.c \
			${EX_FUNC}/ft_export.c \
			${EX_FUNC}/ft_exit.c \
			${EX_FUNC}/ft_unset.c \
			${EX_FUNC}/env_func.c \
			exit.c \
			minishell.c

SOURCE	= $(addprefix $(SRC)/, $(SOURCES))

FLAGS	= -Wall -Wextra -Werror

OBJECTS	= ${SOURCE:.c=.o}

all: ${NAME}

$(NAME): ${OBJECTS}
	make bonus -C ${FT}
	gcc -I ${INC} $(OBJECTS) -l ft -L ${FT} -o $(NAME)

%.o: %.c ${HFILES}
	gcc ${FLAGS} -I ${INC} -c $< -o $@

clean:
	make clean -C ${FT}
	rm -f ${OBJECTS}
fclean: clean
	make fclean -C ${FT}
	rm -f ${NAME}
re: fclean all

norm:
	norminette ex_func/*

.PHONY: all clean fclean re

