/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:54:11 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:07:08 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

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

void	*ft_memset(void *s, int c, size_t n);
char	*ft_strrchr(const char *s, int c);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s);
void	safe_free(void *ptr);

#endif
