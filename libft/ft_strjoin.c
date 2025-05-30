/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:52:24 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/19 12:02:37 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	tlen;
	char	*fstr;

	tlen = ft_strlen(s1) + ft_strlen(s2);
	fstr = malloc(sizeof(char) * (tlen + 1));
	if (fstr == NULL)
		return (NULL);
	fstr[0] = '\0';
	ft_strlcat(fstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(fstr, s2, tlen + 1);
	return (fstr);
}
