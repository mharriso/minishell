/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharriso <mharriso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 01:34:10 by mharriso          #+#    #+#             */
/*   Updated: 2021/03/27 21:57:08 by mharriso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

/*
********************************FIRST PART********************************* *
*/

size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t number, size_t size);
void			ft_bzero(void *s, size_t n);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *str);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dest, const void *source, size_t count);
void			*ft_memccpy(void *dst, const void *src, int c, size_t count);
int				ft_memcmp(const void *buf1, const void *buf2, size_t count);
void			*ft_memchr(const void *arr, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
int				ft_atoi(char *str);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isalnum(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
********************************SECOND PART******************************** *
*/

char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
********************************BONUS PART********************************* *
*/

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
int				get_next_line(int fd, char **line);
char			**ft_split_set(char const *s, char *set, size_t *len);
int				ft_strcmp(const char *s1, const char *s2);

#endif
