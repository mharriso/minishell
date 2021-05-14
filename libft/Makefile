NAME		= libft.a
FLAGS		= -Wall -Werror -Wextra
FILES		= ft_strlen.c \
				ft_calloc.c \
				ft_bzero.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strnstr.c \
				ft_strncmp.c \
				ft_strdup.c \
				ft_memset.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memcmp.c \
				ft_memchr.c\
				ft_memmove.c \
				ft_atoi.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isalnum.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_substr.c \
				ft_putstr_fd.c \
				ft_putchar_fd.c \
				ft_putnbr_fd.c \
				ft_putendl_fd.c
OBJ			= $(FILES:.c=.o)

BONUS_FILES = ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstlast.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstmap.c \
				ft_lstiter.c \
				ft_split_set.c \
				ft_strcmp.c \
				get_next_line.c

OBJ_BONUS = $(BONUS_FILES:.c=.o)

all: $(NAME)

%.o: %.c
	gcc -c $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

bonus: $(OBJ) $(OBJ_BONUS)
	ar rc $(NAME) $(OBJ) $(OBJ_BONUS)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
