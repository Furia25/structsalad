/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:28 by vdurand           #+#    #+#             */
/*   Updated: 2025/06/24 16:25:29 by vdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdbool.h>

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 10
# endif

typedef struct s_gnl_result
{
	int		error;
	int		ended;
	char	*line;
}	t_gnl_result;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
//
size_t			ft_intlen(int n);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dest, char *src, size_t size);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
long			ft_strchri(char *s, int c);
//
int				ft_putnbr_base_fd(long nb, char *base, int fd);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strend(char *str, char *suffix);
int				count_words(const char *str, char c);
int				ft_atoi(const char *nptr);
int				ft_lstsize(t_list *lst);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_isbigendian(void);
//
char			**ft_split(char const *s, char c);
//
char			*ft_strcat(char *dest, const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strrchr(const char *s, int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
t_gnl_result	get_next_line(int fd);
char			*ft_itoa(int n);
void			ft_itoab(int n, wchar_t *res, int len);
//
void			ft_striteri(char *s, void (*f)(size_t, char *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_putendl_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_bzero(void *s, size_t n);
void			free_chartab(char **tab);
//
void			*ft_calloc(size_t elementCount, size_t elementSize);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *pointer, int value, size_t count);

#endif