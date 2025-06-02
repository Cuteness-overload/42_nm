/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:21:23 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:55 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_memset(void *s, int c, size_t n)
// {
// 	unsigned char	*ptr;
// 	unsigned int	pattern;
// 	size_t			aligned_bytes;
// 	size_t			i;
// 	size_t			j;

// 	i = 0;
// 	j = 0;
// 	ptr = s;
// 	pattern = (unsigned char)c * 0x01010101u;
// 	while (i < n && ((long)(ptr + i) % sizeof(unsigned int)) != 0)
// 		ptr[i++] = (unsigned char)c;
// 	aligned_bytes = (n - i) / sizeof(unsigned int);
// 	while (j < aligned_bytes)
// 		((unsigned int *)(ptr + i))[j++] = pattern;
// 	j = 0;
// 	ptr += i + aligned_bytes * sizeof(unsigned int);
// 	while (j < (n - i) % sizeof(unsigned int))
// 		ptr[j++] = (unsigned char)c;
// 	return (s);
// }

// char	*ft_strrchr(const char *s, int c)
// {
// 	int	i;

// 	i = ft_strlen(s);
// 	while (i >= 0)
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)&s[i]);
// 		i--;
// 	}
// 	return (NULL);
// }

// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	str = malloc(ft_strlen(s) + 1);
// 	if (!str)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		str[i] = s[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}
