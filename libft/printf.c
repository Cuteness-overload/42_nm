/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:56:18 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:08 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_data(t_data *data, const char *str)
{
	data->s = str;
	data->idx = 0;
	data->chars_written = 0;
	data->err = 0;
	ft_memset(data->buf, 0, BUFFER_SIZE);
	data->buf_idx = 0;
}

int	ft_printf(const char *str, ...)
{
	t_data	data;

	if (str == 0)
		return (0);
	va_start(data.ap, str);
	init_data(&data, str);
	while (data.s[data.idx])
	{
		data.idx++;
		if (data.s[data.idx - 1] == '%')
		{
			if (parser(&data))
				return (PARSE_ERROR);
			if (render(&data))
				return (data.err);
		}
		else
			if (putchar_buf(&data, 1, data.s[data.idx - 1]))
				return (WRITE_ERROR);
	}
	if (print_buf(&data))
		return (WRITE_ERROR);
	return (data.chars_written);
}
