/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:15:40 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/30 17:31:26 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		add_node(t_node **node, t_node *new)
{
	new->next = *node;
	*node = new;
//    t_node     *temp;
//
//    temp = *node;
//    while (temp && temp->next)
//    {
//        temp = temp->next;
//    }
//	temp->next = *node;
}

t_node		*new_node(t_graph **graph, t_info *info, int node)
{
	t_node      *new;

	if (!(new = ((t_node *)malloc(sizeof(*new)))))
		error("Memory allocation error\n", graph, info);
	new->node = node;
	new->next = NULL;
	
	return (new);
}

t_path		*new_path(t_graph **graph, t_info *info)
{
	t_path      *new;

	if (!(new = ((t_path *)malloc(sizeof(*new)))))
		error("Memory allocation error\n", graph, info);
	new->length = 0;
	new->stack = 0;
	new->node = NULL;
	new->next = NULL;
	
	return (new);
}

void		add_path(t_path **path, t_path *new)
{
	new->next = *path;
	*path = new;
}

void		free_path(t_path **path)
{
	t_path *ptr;

	while (*path)
	{
		ptr = *path;
		*path = (*path)->next;
		free(ptr);
		ptr = NULL;
	}
}