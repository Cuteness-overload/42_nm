/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 06:05:02 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/05/24 18:05:29 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	head = NULL;
	while (lst != NULL)
	{
		if (head == NULL)
		{
			head = ft_lstnew(f(lst->content));
			if (head == NULL)
				return (NULL);
		}
		else
		{
			tmp = ft_lstnew(f(lst->content));
			if (tmp == NULL)
				return (ft_lstclear(&head, del), NULL);
			ft_lstadd_back(&head, tmp);
		}
		lst = lst->next;
	}
	return (head);
}
