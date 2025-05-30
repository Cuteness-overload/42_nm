/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:11:30 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:36 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_long(t_data *data, long n)
{
	char	*res;

	res = ft_ltoa(n, data->form.base, data);
	if (!res)
		return (MALLOC_ERROR);
	check_null_prec(data, res);
	set_plus(data, n);
	set_zeros(data, n);
	check_neg_width(data);
	if (data->form.minus)
	{
		data->err += print_sign_hash_space(data, n);
		data->err += putchar_buf(data, data->form.o_pad, '0');
		data->err += putstr_buf(data, ft_strlen(res), res);
		data->err += pad_spaces(data, n);
	}
	else
	{
		data->err += pad_spaces(data, n);
		data->err += print_sign_hash_space(data, n);
		data->err += putchar_buf(data, data->form.o_pad, '0');
		data->err += putstr_buf(data, ft_strlen(res), res);
	}
	return (safe_free(res), data->err);
}

int	print_point(t_data *data, unsigned long n)
{
	char	*res;

	res = ft_ultoa(n);
	if (!res)
		return (MALLOC_ERROR);
	check_neg_width(data);
	set_zeros(data, (long)n);
	data->form.plus = 0;
	if (data->form.minus)
	{
		data->err += putstr_buf(data, 2, "0x");
		data->err += putchar_buf(data, data->form.o_pad, '0');
		data->err += putstr_buf(data, ft_strlen(res), res);
		data->err += pad_spaces(data, n);
	}
	else
	{
		data->err += pad_spaces(data, n);
		data->err += putstr_buf(data, 2, "0x");
		data->err += putchar_buf(data, data->form.o_pad, '0');
		data->err += putstr_buf(data, ft_strlen(res), res);
	}
	return (safe_free(res), data->err);
}

int	ft_numlen_point(unsigned long n, int base)
{
	int	len;

	len = 1;
	if (n < 0)
		n = -n;
	while (n > (unsigned long)base - 1)
	{
		len++;
		n /= (unsigned long)base;
	}
	return (len);
}
