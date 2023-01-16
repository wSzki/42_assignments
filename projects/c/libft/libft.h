/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:26:39 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/12 21:54:43 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
char			*ft_itoa(int n);

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isupper(int c);
int				ft_islower(int c);

size_t			ft_count_words(const char *str, char c);
int				ft_is_c(const char c1, const char c2);

void			ft_bzero(void *s, size_t nb);
void			*ft_memcpy(void *dest, const void *src, size_t count);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *ptr, int ch, size_t count);
void			*ft_memmove(void *dest, const void *src, size_t count);
void			*ft_memset(void *dest, int ch, size_t count);
int				ft_memcmp(const void *s1, const void *s2, size_t size);
void			*ft_memalloc(size_t size);

char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t nb);
size_t			ft_strlcat(char *dest, const char *src, size_t size);

char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strdup(const char *src);
char			*ft_strndup(const char *src, size_t n);

char			*ft_strchr(const char *str, int ch);
char			*ft_strrchr(const char *str, int ch);

int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

size_t			ft_strlen(const char *str);

char			*ft_strstr(const char *str, const char *to_find);
char			*ft_strnstr(const char *big, const char *little, size_t len);

int				ft_tolower(int c);
int				ft_toupper(int c);

size_t			ft_strlcpy(char *dest, const char *src, size_t size);

char			*ft_strjoin(const char *s1, const char *s2);
char			**ft_split(const char *str, char c);

void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);

void			ft_putstr(const char *s);
void			ft_putendl(const char *s);
int				ft_putchar(int c);
void			ft_putnbr(int n);

void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strmap(const char *s, char (*f)(char));

void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char *s, int fd);

int				ft_lstsize(t_list *lst);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstadd_front(t_list **first, t_list *new);
void			ft_lstadd_back(t_list **first, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **list, void (*del)(void *));
t_list			*ft_lstmap
				(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
