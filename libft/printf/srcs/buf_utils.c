/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:29:19 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:23:49 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_buf(t_data *data, int n, char c)
{
	while (n-- > 0)
	{
		if (data->buf_idx == BUFFER_SIZE)
			if (print_buf(data))
				return (WRITE_ERROR);
		data->buf[data->buf_idx++] = c;
	}
	return (OK);
}

int	putstr_buf(t_data *data, int len, char *str)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (data->buf_idx == BUFFER_SIZE)
			if (print_buf(data))
				return (WRITE_ERROR);
		data->buf[data->buf_idx++] = str[i++];
	}
	return (OK);
}

int	print_buf(t_data *data)
{
	if (write(1, &data->buf, data->buf_idx) < 0)
		return (WRITE_ERROR);
	data->chars_written += data->buf_idx;
	data->buf_idx = 0;
	return (OK);
}
