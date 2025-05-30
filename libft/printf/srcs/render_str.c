/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:13:34 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:47 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_data *data, char c)
{
	if (data->form.minus)
	{
		data->err += putchar_buf(data, 1, c);
		data->err += putchar_buf(data, data->form.width - 1, ' ');
	}
	else
	{
		data->err += putchar_buf(data, data->form.width - 1, ' ');
		data->err += putchar_buf(data, 1, c);
	}
	if (data->err)
		return (WRITE_ERROR);
	return (OK);
}

int	print_str(t_data *data, char *str)
{
	int	len;

	str = check_null(data, str);
	if (!str)
		return (MALLOC_ERROR);
	len = precise_len(data, str);
	if (data->form.minus)
	{
		data->err += putstr_buf(data, len, str);
		data->err += putchar_buf(data, data->form.width - len, ' ');
	}
	else
	{
		data->err += putchar_buf(data, data->form.width - len, ' ');
		data->err += putstr_buf(data, len, str);
	}
	if (data->form.null)
		safe_free(str);
	if (data->err)
		return (WRITE_ERROR);
	return (OK);
}
