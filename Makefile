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
ENV_F	=	env_func
SIGNAL	=	signal

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
			history_utils.h \
			ft_signal.h

HFILES	=	$(addprefix $(INC)/, $(HEADER))

SRC_DLST	=	dlist_f.c \
				dlist_f2.c

SRC_TSTR	=	tstr_init.c \
				tstr_edit.c

SRC_UTILS	=	check_long_long.c \
				exit.c \
				get_full_path.c \
				com_func.c \
				red_func.c\
				commands_handler.c \
				sort_env.c \
				print_error.c \
				wildcard.c \
				com_get.c \
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

SRC_PARSER	=	run_parser.c \
				parse_line.c \
				parser_utils.c \
				tokens_utils.c \
				tokens_utils2.c \
				tokens_handler.c \
				env_handler.c \
				create_com_lst.c

SRC_HISTORY	=	his_edit.c \
				his_get_fname.c \
				his_get_mslvl.c \
				his_init.c

SRC_TERM	=	ft_term.c \
				term_cur_hor.c \
				term_cur_vert.c \
				term_write.c \
				utils.c \
				term_attr.c

SRC_ENV_F	=	env_creation.c \
				env_get.c \
				env_utils.c

SRC_SIGNAL	=	signal.c

SRC_F	=	$(addprefix $(UTILS)/, $(SRC_UTILS)) \
			$(addprefix $(BUILDIN)/, $(SRC_BUILDIN)) \
			$(addprefix $(FORK)/, $(SRC_FORK)) \
			$(addprefix $(PARSER)/, $(SRC_PARSER)) \
			$(addprefix $(HISTORY)/, $(SRC_HISTORY)) \
			$(addprefix $(TERM)/, $(SRC_TERM)) \
			$(addprefix $(ENV_F)/, $(SRC_ENV_F)) \
			$(addprefix $(SIGNAL)/, $(SRC_SIGNAL))

SOURCES	= $(addprefix $(SRC)/, $(SRC_F))

SOURCE = ${SOURCES} ${SRC}/minishell.c

FLAGS	= -Wall -Wextra -Werror

OBJECTS	= ${SOURCE:.c=.o}


all: ${NAME}

$(NAME): ${OBJECTS}
	make bonus -C ${FT}
	gcc -I ${INC} $(OBJECTS) -ltermcap -l ft -L ${FT} -o $(NAME)

%.o: %.c ${HFILES}
	gcc ${FLAGS} -I ${INC} -c $< -o $@

clean:
	make clean -C ${FT}
	rm -f ${OBJECTS}
fclean: clean
	make fclean -C ${FT}
	rm -f ${NAME}
re: fclean all

bonus: ${NAME}

norm:
	norminette src/* inc/*

.PHONY: all clean fclean re bonus
