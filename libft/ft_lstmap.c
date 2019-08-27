/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:25:12 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 20:55:08 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *ptr;
	t_list *copy;

	copy = NULL;
	ptr = copy;
	if (lst == NULL || f == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if ((copy = ft_lstnew(lst->content, lst->content_size)) == NULL)
			return (NULL);
		copy = f(copy);
		ft_lstadd_back(&ptr, copy);
		lst = lst->next;
	}
	return (ptr);
}
