NAME	=	minishell
SRC		=	src
EX_FUNC =	ex_func
FT		=	libft
INC		=	inc
UTILS	=	utils

HEADER	=	ex_func.h \
			exit.h \
			env_func.h\
			libft.h

HFILES	=	$(addprefix $(INC)/, $(HEADER))


SRC_UTILS	=	check_long_long.c \
				exit.c \
				env_func.c

SRC_EX_FUN	=	ft_pwd.c \
				ft_cd.c \
				ft_env.c \
				ft_export.c \
				ft_exit.c \
				ft_unset.c 

SRC_F	=	$(addprefix $(UTILS)/, $(SRC_UTILS)) \
			$(addprefix $(EX_FUNC)/, $(SRC_EX_FUN)) \

SOURCES	= $(addprefix $(SRC)/, $(SRC_F))

SOURCE = ${SOURCES} ${SRC}/minishell.c

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

