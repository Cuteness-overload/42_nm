/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:47:30 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/20 02:52:00 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dest, const char *src, size_t n)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;
	size_t	space_left;

	i = 0;
	src_len = ft_strlen(src);
	if (n == 0)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (dest_len < n)
	{
		space_left = n - dest_len - 1;
		while (i < space_left && i < src_len)
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		dest[dest_len + i] = '\0';
		return (src_len + dest_len);
	}
	return (src_len + n);
}
