/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:33:56 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/05/24 17:03:49 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	size_t	count;
	size_t	j;

	count = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] != c)
		{
			count++;
			while (str[j] && str[j] != c)
				j++;
		}
		else if (str[j] == c)
			j++;
	}
	return (count);
}

static void	free_strings(char **arr, size_t count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	free(arr);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**splitter(char const *s, char c, char **arr, size_t wrd_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < wrd_count)
	{
		while (s[j] && s[j] == c)
			j++;
		arr[i] = ft_substr(s, j, word_len(&s[j], c));
		if (!arr[i])
		{
			free_strings(arr, i);
			return (NULL);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	counts;
	char	**arr;

	if (!s)
		return (NULL);
	counts = count_words(s, c);
	arr = malloc(sizeof(char *) * (counts + 1));
	if (!arr)
		return (NULL);
	arr = splitter(s, c, arr, counts);
	return (arr);
}
