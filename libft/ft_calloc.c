/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:10:02 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/20 06:49:49 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_overflow(size_t a, size_t b)
{
	int	result;

	if (a == 0 || b == 0)
		return (0);
	result = a * b;
	if (a == result / b)
		return (0);
	else
		return (1);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*arr;

	if (is_overflow(num, size))
		return (NULL);
	arr = malloc(num * size);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, num * size);
	return (arr);
}
