/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:01:26 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:51 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	render_num(t_data *data)
{
	unsigned long	n;

	if (data->form.field == 'd' || data->form.field == 'i')
		data->err = print_long(data, (long)va_arg(data->ap, int));
	else if (ft_strrchr("uxX", data->form.field))
		data->err = print_long(data, (long)va_arg(data->ap, unsigned int));
	else if (data->form.field == 'p')
	{
		n = (unsigned long)va_arg(data->ap, void *);
		if (n == 0)
			data->err = print_nil(data);
		else
			data->err = print_point(data, n);
	}
	return (data->err);
}

int	render(t_data *data)
{
	if (data->form.field == '%')
		data->err = putchar_buf(data, 1, '%');
	else if (data->form.field == 'c')
		data->err = print_char(data, (char)va_arg(data->ap, int));
	else if (data->form.field == 's')
		data->err = print_str(data, va_arg(data->ap, char *));
	else if (ft_strrchr("diuxXp", data->form.field))
		data->err = render_num(data);
	return (data->err);
}
