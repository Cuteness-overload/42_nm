/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:31:18 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/20 03:58:32 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_slen(int n)
{
	size_t	slen;

	slen = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		slen++;
		n *= -1;
	}
	while (n > 9)
	{
		slen++;
		n /= 10;
	}
	return (slen);
}

static int	check_edge_cases(char *str, int n)
{
	if (n == 0)
		str[0] = '0';
	if (n == -2147483648)
	{
		str[1] = '2';
		n = -147483648;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	size_t	slen;
	char	*str;

	slen = get_slen(n);
	str = malloc(sizeof(char) * (slen + 1));
	if (str == NULL)
		return (NULL);
	n = check_edge_cases(str, n);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[slen--] = '\0';
	while (n != 0)
	{
		str[slen--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
