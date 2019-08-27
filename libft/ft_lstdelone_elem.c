/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_elem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:46:00 by bdudley           #+#    #+#             */
/*   Updated: 2018/12/15 01:36:40 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone_elem(t_list **lst, void *content,
		int (*f)(void *content1, void *content2), void (*del)(void*, size_t))
{
	t_list **ptr;
	t_list *d;

	ptr = lst;
	if (del == NULL || *lst == NULL || f == NULL ||
		!(*lst = ft_find_elem(*lst, content, f)))
		return ;
	d = (*lst)->next;
	(*lst)->next = (*lst)->next->next;
	ft_lstdelone(&d, del);
	lst = ptr;
}
