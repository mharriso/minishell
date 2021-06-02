NAME	=	minishell
SRC		=	src
BUILDIN =	buildin
FT		=	libft
INC		=	inc
UTILS	=	utils
PARSER	=	parser
FORK	=	fork
HISTORY	=	history
TERM	=	term
DLST	=	dlist
TSTR	=	tstr

HEADER	=	buildin.h \
			exit.h \
			env_func.h\
			libft.h \
			structs.h \
			utils.h \
			fork.h \
			com_func.h \
			red_func.h \
			parser.h \
			dlist.h \
			tstr.h \
			ft_term.h \
			term_utils.h \
			history.h \
			history_utils.h

HFILES	=	$(addprefix $(INC)/, $(HEADER))

SRC_DLST	=	dlist_f.c \
				dlist_f2.c

SRC_TSTR	=	tstr_init.c \
				tstsr_edit.c

SRC_UTILS	=	check_long_long.c \
				exit.c \
				env_func.c \
				get_full_path.c \
				com_func.c \
				red_func.c\
				commands_handler.c \
				$(addprefix $(DLST)/, $(SRC_DLST)) \
				$(addprefix $(TSTR)/, $(SRC_TSTR))

SRC_BUILDIN	=	ft_pwd.c \
				ft_cd.c \
				ft_env.c \
				ft_export.c \
				ft_exit.c \
				ft_unset.c \
				ft_echo.c \
				ft_runbuildin.c

SRC_FORK	=	redirect.c \
				fork.c\
				pipe.c

SRC_PARSER	=	parser.c \
				parser_utils.c

SRC_HISTORY	=	his_edit.c \
				his_get_fname.c \
				his_get_mslvl.c \
				his_init.c

SRC_TERM	=	ft_term.c \
				term_cur_hor.c \
				term_cur_vert.c \
				term_write.c \
				utils.c

SRC_F	=	$(addprefix $(UTILS)/, $(SRC_UTILS)) \
			$(addprefix $(BUILDIN)/, $(SRC_BUILDIN)) \
			$(addprefix $(FORK)/, $(SRC_FORK)) \
			$(addprefix $(PARSER)/, $(SRC_PARSER)) \
			$(addprefix $(HISTORY)/, $(SRC_HISTORY)) \
			$(addprefix $(TERM)/, $(SRC_TERM))

SOURCES	= $(addprefix $(SRC)/, $(SRC_F))

SOURCE = ${SOURCES} ${SRC}/minishell.c

FLAGS	= -Wall -Wextra -Werror

OBJECTS	= ${SOURCE:.c=.o}


##############  TEST_BEGIN  ##################

S_NAME	=	s_test.out
Y_NAME	=	y_test.out

S_SOURCE	= ${SOURCES} ${SRC}/s_main.c
Y_SOURCE	= ${SOURCES} ${SRC}/y_main.c

S_OBJECTS	= ${S_SOURCE:.c=.o}
Y_OBJECTS	= ${Y_SOURCE:.c=.o}

##############  TEST_END  ##################


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
	norminette src/* inc/*

##############  TEST_BEGIN  ##################

s_test: ${S_OBJECTS}
	make bonus -C ${FT}
	gcc -I ${INC} $(S_SOURCE) -g -l ft -L ${FT} -o ${S_NAME}
s_clean:
	make clean -C ${FT}
	rm -f ${S_OBJECTS}
s_fclean: s_clean
	make fclean -C ${FT}
	rm -f ${S_NAME}
s_re: s_fclean s_test

y_test: ${Y_OBJECTS}
	make bonus -C ${FT}
	gcc -I ${INC} $(Y_OBJECTS) -l ft -L ${FT} -o ${Y_NAME}
y_clean:
	make clean -C ${FT}
	rm -f ${Y_OBJECTS}
y_fclean: y_clean
	make fclean -C ${FT}
	rm -f ${Y_NAME}
y_re: y_fclean y_test

##############  TEST_END  ##################

.PHONY: all clean fclean re

