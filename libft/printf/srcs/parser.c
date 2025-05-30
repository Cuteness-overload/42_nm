/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:00:38 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:03 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_flags(t_data *data)
{
	while (ft_strrchr(FLAGS, data->s[data->idx]))
	{
		if (data->s[data->idx] == '#')
			data->form.hash = 1;
		else if (data->s[data->idx] == ' ')
			data->form.space = 1;
		else if (data->s[data->idx] == '+')
			data->form.plus = 1;
		else if (data->s[data->idx] == '-')
			data->form.minus = 1;
		else if (data->s[data->idx] == '0')
			data->form.o_pad = 1;
		data->idx++;
	}
}

static void	get_value(t_data *data, int	*num)
{
	int	check;

	check = 0;
	if (data->s[data->idx] == '*')
	{
		*num = va_arg(data->ap, int);
		data->idx++;
		return ;
	}
	while (ft_strrchr(NUMBERS, data->s[data->idx]))
	{
		check = 1;
		if (*num == -1)
			*num = 0;
		*num *= 10;
		*num += data->s[data->idx] - '0';
		data->idx++;
	}
	if (check == 0)
		*num = 0;
	return ;
}

static void	get_base(t_data *data)
{
	if (ft_strrchr("diu", data->form.field))
		data->form.base = 10;
	else if (ft_strrchr("xXp", data->form.field))
		data->form.base = 16;
}

int	parser(t_data *data)
{
	ft_memset(&data->form, 0, sizeof(t_format));
	data->form.prec = -1;
	get_flags(data);
	get_value(data, &data->form.width);
	if (data->s[data->idx] == '.' && data->idx++)
		get_value(data, &data->form.prec);
	if (!ft_strrchr(FIELD, data->s[data->idx]))
		return (PARSE_ERROR);
	data->form.field = data->s[data->idx++];
	get_base(data);
	return (OK);
}
