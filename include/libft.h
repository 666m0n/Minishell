/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sviallon <sviallon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:11:41 by sviallon          #+#    #+#             */
/*   Updated: 2024/10/24 15:14:30 by sviallon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <ctype.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdarg.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

// libft 1.1
int		ft_atoi(const char *nptr);
void	ft_bzero(void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *src, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t siz);
size_t	ft_strlcpy(char *dest, const char *src, size_t siz);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);

// ft_printf
int		ft_hexalen(unsigned long n);
int		ft_putchar(int c);
int		ft_conversions(va_list args, const char conversions);
int		ft_printf(const char *str, ...);
int		ft_putstr(char *str);
int		ft_putnbr(int nb);
int		ft_intlen(long long n);
void	ft_putnbr_hexa(unsigned long n, const char base);
int		ft_printhexa(unsigned int num, const char conversions);
int		ft_putunbr(unsigned int nb);
int		ft_printptr(void *n, const char conversions);

// gnl
char	*get_next_line(int fd);
void	read_and_stash(int fd, t_list **stash);
void	add_to_stash(t_list **stash, char *buf, int lus);
void	extract_line(t_list *stash, char **line);
void	clean_stash(t_list **stash);
void	free_stash(t_list *stash);
size_t	ft_strlen(const char *s);
void	malloc_line(char **line, t_list *stash);
t_list	*ft_lst_get_last(t_list *stash);
int		found_newline(t_list *stash);
t_list	*create_clean_node(t_list *last, int i);

#endif
