/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:10:48 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 17:48:15 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *copy;
	t_list *tmp;

	if (*alst == NULL || alst == NULL || del == NULL)
		return ;
	copy = *alst;
	while (copy != NULL)
	{
		tmp = copy;
		copy = copy->next;
		ft_lstdelone(&tmp, del);
	}
	*alst = NULL;
}
