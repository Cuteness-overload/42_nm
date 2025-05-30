/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_num_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:31:13 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:26 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_numlen(long n, int base)
{
	int	len;

	len = 1;
	if (n < 0)
		n = -n;
	while (n > base - 1)
	{
		len++;
		n /= base;
	}
	return (len);
}

char	*ft_ltoa(long n, int base, t_data *data)
{
	char	*res;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_numlen(n, base);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		if (base == 10)
			res[--len] = n % base + '0';
		else if (base == 16 && data->form.field == 'x')
			res[--len] = HEX_L[n % base];
		else if (base == 16 && data->form.field == 'X')
			res[--len] = HEX_U[n % base];
		n /= base;
	}
	return (res);
}

char	*ft_ultoa(unsigned long n)
{
	int		len;
	char	*res;

	len = ft_numlen_point(n, 16);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (n > 0)
	{
		res[--len] = HEX_L[n % 16];
		n /= 16;
	}
	return (res);
}

int	print_nil(t_data *data)
{
	if (data->form.minus)
	{
		data->err += putstr_buf(data, 5, "(nil)");
		data->err += putchar_buf(data, data->form.width - 5, ' ');
	}
	else
	{
		data->err += putchar_buf(data, data->form.width - 5, ' ');
		data->err += putstr_buf(data, 5, "(nil)");
	}
	return (data->err);
}

void	check_null_prec(t_data *data, char *str)
{
	if (str[0] == '0' && data->form.prec == 0)
		str[0] = '\0';
}
