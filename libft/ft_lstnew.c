/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 20:18:11 by bdudley           #+#    #+#             */
/*   Updated: 2019/07/20 17:15:29 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *p;

	if (!(p = (t_list *)malloc(sizeof(*p))))
		return (NULL);
	if (content == NULL)
	{
		p->next = NULL;
		p->content_size = 0;
		p->content = NULL;
	}
	else if (!(p->content = malloc(content_size)))
	{
		free(p);
		return (NULL);
	}
	else
	{
		p->content_size = content_size;
		p->content = ft_memcpy(p->content, content, content_size);
		p->next = NULL;
	}
	return (p);
}
