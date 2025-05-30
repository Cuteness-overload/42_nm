/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:09:02 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/19 23:16:55 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned int	pattern;
	size_t			aligned_bytes;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	ptr = s;
	pattern = (unsigned char)c * 0x01010101u;
	while (i < n && ((long)(ptr + i) % sizeof(unsigned int)) != 0)
		ptr[i++] = (unsigned char)c;
	aligned_bytes = (n - i) / sizeof(unsigned int);
	while (j < aligned_bytes)
		((unsigned int *)(ptr + i))[j++] = pattern;
	j = 0;
	ptr += i + aligned_bytes * sizeof(unsigned int);
	while (j < (n - i) % sizeof(unsigned int))
		ptr[j++] = (unsigned char)c;
	return (s);
}
