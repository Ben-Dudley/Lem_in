/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 23:21:12 by bdudley           #+#    #+#             */
/*   Updated: 2018/12/15 01:29:50 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_find_elem(t_list *lst, void *content,
		int (*f)(void *content1, void *content2))
{
	while (lst != NULL)
	{
		if (f(lst->content, content) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
