/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:15:40 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/04 16:20:44 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		add_node(t_node **node, t_node *new)
{
	new->next = *node;
	*node = new;
}

t_node		*new_node(t_graph **graph, t_info *info, int node)
{
	t_node		*new;

	if (!(new = ((t_node *)malloc(sizeof(*new)))))
		error_message(graph, info, 0);
	new->node = node;
	new->ant = 0;
	new->next = NULL;
	return (new);
}

t_path		*new_path(t_graph **graph, t_info *info)
{
	t_path		*new;

	if (!(new = ((t_path *)malloc(sizeof(*new)))))
		error_message(graph, info, 0);
	new->length = 0;
	new->node = NULL;
	new->next = NULL;
	return (new);
}

void		add_path(t_path **path, t_path *new)
{
	new->next = *path;
	*path = new;
}

void		restoration_path(t_graph **graph, t_info *info, int *traces)
{
	int			i;
	t_link		*temp;

	i = info->ind_end;
	while (i != info->ind_start)
	{
		temp = graph[0][traces[i]].link;
		while (temp)
		{
			if (temp->node == i)
			{
				if (traces[i] != info->ind_start)
					graph[0][traces[i]].visited = 1;
				temp->status = 0;
//				printf("!!!!!!!!!!!!!!!!!queue[%d] %s(%d)\n",i, graph[0][traces[i]].name, graph[0][traces[i]].visited);
//				printf("±!±±±±±±±±±±±±±±±±ptr->node %s (%d, %d)\n", graph[0][temp->node].name, temp->status, temp->reverse->status);
				break ;
			}
			temp = temp->next;
		}
		i = traces[i];
	}
}
