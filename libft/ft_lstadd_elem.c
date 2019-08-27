/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:04:32 by bdudley           #+#    #+#             */
/*   Updated: 2018/12/15 01:35:52 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_elem(t_list **lst, void *content,
		t_list *new, int (*f)(void *content1, void *content2))
{
	t_list **ptr;

	ptr = lst;
	if (new == NULL || *lst == NULL || f == NULL ||
		!(*lst = ft_find_elem(*lst, content, f)))
		return ;
	new->next = (*lst)->next;
	(*lst)->next = new;
	lst = ptr;
}
