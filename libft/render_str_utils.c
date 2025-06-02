/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:39:38 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:42 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_null(t_data *data, char *str)
{
	char	*nstr;

	if (!str)
	{
		nstr = ft_strdup("(null)");
		if (!nstr)
			return (NULL);
		if (data->form.prec >= 0 && data->form.prec < 6)
			data->form.prec = 0;
		else
			data->form.prec = 6;
		data->form.null = 1;
		return (nstr);
	}
	return (str);
}

int	precise_len(t_data *data, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (data->form.prec >= 0 && data->form.prec < len)
		len = data->form.prec;
	return (len);
}
