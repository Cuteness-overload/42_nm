/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:39:53 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/18 12:39:53 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *nptr);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char	*dest, const char *src, size_t n);
size_t	ft_strlcpy(char	*dest, const char *src, size_t n);
void	*ft_calloc(size_t num, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);

char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

# define BUFFER_SIZE 1024
# define FLAGS "# +-0"
# define FIELD "cspdiuxX%"
# define NUMBERS "0123456789"
# define HEX_L "0123456789abcdef"
# define HEX_U "0123456789ABCDEF"

enum e_error
{
	OK = 0,
	MALLOC_ERROR = -1,
	PARSE_ERROR = -2,
	WRITE_ERROR = -3,
};

typedef struct s_format
{
	char	field;
	int		null;

	int		minus;
	int		o_pad;
	int		prec;
	int		hash;
	int		space;
	int		plus;
	int		width;

	int		base;
}	t_format;

typedef struct s_data
{
	const char	*s;
	int			idx;
	char		buf[BUFFER_SIZE];
	int			buf_idx;
	int			chars_written;
	int			err;
	va_list		ap;
	t_format	form;

}	t_data;

int		ft_printf(const char *str, ...);
int		parser(t_data *data);
int		render(t_data *data);

int		putchar_buf(t_data *data, int n, char c);
int		putstr_buf(t_data *data, int len, char *str);
int		print_buf(t_data *data);

int		print_char(t_data *data, char c);
int		print_str(t_data *data, char *str);

char	*check_null(t_data *data, char *str);
int		precise_len(t_data *data, char *str);

int		print_long(t_data *data, long n);
int		print_point(t_data *data, unsigned long n);
int		ft_numlen_point(unsigned long n, int base);

char	*ft_ltoa(long n, int base, t_data *data);
char	*ft_ultoa(unsigned long n);
int		ft_numlen(long n, int base);
int		print_nil(t_data *data);
void	check_null_prec(t_data *data, char *str);

void	set_plus(t_data *data, long n);
void	check_neg_width(t_data *data);
int		pad_spaces(t_data *data, long n);
int		print_sign_hash_space(t_data *data, long n);
void	set_zeros(t_data *data, long n);

void	safe_free(void *ptr);

#endif
