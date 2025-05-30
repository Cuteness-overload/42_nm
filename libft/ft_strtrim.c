/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:06:16 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/20 03:24:10 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_charset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && in_charset(s1[start], set))
		start++;
	while (start != end && in_charset(s1[end - 1], set))
		end--;
	trimmed = malloc(sizeof(char) * ((end - start) + 1));
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, &s1[start], (end - start) + 1);
	return (trimmed);
}
