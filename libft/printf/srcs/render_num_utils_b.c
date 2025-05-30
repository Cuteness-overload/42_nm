/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_num_utils_b.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:45:46 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:14 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_plus(t_data *data, long n)
{
	if (n < 0)
		data->form.plus = 1;
	else if (ft_strrchr("xX", data->form.field))
		data->form.plus = 0;
}

void	check_neg_width(t_data *data)
{
	if (data->form.width < 0)
	{
		data->form.width = -data->form.width;
		data->form.minus = 1;
	}
}

int	pad_spaces(t_data *data, long n)
{
	int	nlen;
	int	pad;

	if (data->form.field == 'p')
		nlen = ft_numlen_point((unsigned long)n, 16);
	else
		nlen = ft_numlen(n, data->form.base);
	if (data->form.space && n >= 0 && !data->form.plus
		&& ft_strrchr("di", data->form.field))
		nlen++;
	if (n == 0 && data->form.prec == 0)
		nlen = 0;
	pad = data->form.width - nlen - data->form.plus - data->form.o_pad;
	if (data->form.hash && ft_strrchr("xX", data->form.field) && n != 0)
		pad -= 2;
	else if (data->form.field == 'p')
		pad -= 2;
	data->err += putchar_buf(data, pad, ' ');
	return (data->err);
}

int	print_sign_hash_space(t_data *data, long n)
{
	if (n >= 0 && ft_strrchr("di", data->form.field))
	{
		if (data->form.plus)
			data->err = putchar_buf(data, 1, '+');
		else if (data->form.space)
			data->err = putchar_buf(data, 1, ' ');
	}
	else if (n < 0)
		data->err = putchar_buf(data, 1, '-');
	if (data->form.hash && data->form.field == 'x' && n != 0)
		data->err = putstr_buf(data, 2, "0x");
	else if (data->form.hash && data->form.field == 'X' && n != 0)
		data->err = putstr_buf(data, 2, "0X");
	return (data->err);
}

void	set_zeros(t_data *data, long n)
{
	int	len;
	int	sign;
	int	hash;

	sign = 0;
	hash = 0;
	if ((ft_strrchr("xX", data->form.field) && data->form.hash && n != 0)
		|| data->form.field == 'p')
		hash = 2;
	len = ft_numlen(n, data->form.base);
	if (data->form.plus || data->form.space)
		sign = 1;
	if (data->form.o_pad && !data->form.minus && data->form.prec < 0)
		data->form.o_pad = data->form.width - len - sign - hash;
	else if (data->form.prec >= 0)
		data->form.o_pad = data->form.prec - len;
	else if (data->form.o_pad == 1)
		data->form.o_pad = 0;
	if (data->form.o_pad < 0)
		data->form.o_pad = 0;
}
