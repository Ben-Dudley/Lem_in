/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:28:53 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/19 18:11:31 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link	*new_link(char *node1, char *node2)
{
	t_link *new;

	new = (t_link *)malloc(sizeof(*new));
	new->node_1 = node1;
	new->node_2 = node2;
	new->next = NULL;
	return (new);
}

void	add_link(t_link **link, t_link *new)
{
	new->next = *link;
	*link = new;
}

void 	free_link(t_link **link)
{
	t_link *ptr;

	while (*link)
	{
		free((*link)->node_1);
		(*link)->node_1 = NULL;
		free((*link)->node_2);
		(*link)->node_2 = NULL;
		ptr = *link;
		*link = (*link)->next;
		free(ptr);
		ptr = NULL;
	}
}