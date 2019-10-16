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

void		restoration_path(t_graph **graph, t_info *info, t_trace *trace)
{
	int			i;
	t_link		*temp;

	//printf("%d, %d\n", info->ind_start, info->ind_end);
	i = info->ind_end;
	while (i != info->ind_start)
	{
		temp = graph[0][trace->traces_0[i]].link;
		while (temp)
		{
			if (temp->node == i)
			{
				temp->status = 0;
				//printf("SSSSS %d", temp->status + temp->reverse->status);
				if ((trace->traces_1[trace->traces_0[i]] != -1 && temp->status + temp->reverse->status == 1 && graph[0][trace->traces_0[i]].visited == 1)
				|| trace->traces_0[trace->traces_0[i]] == -1)
					trace->traces_0[trace->traces_0[i]] = trace->traces_1[trace->traces_0[i]];
				if (trace->traces_0[i] != info->ind_start)
					graph[0][trace->traces_0[i]].visited = 1;
				break ;
			}
			temp = temp->next;
		}
		i = trace->traces_0[i];
//		printf("[%d] ", i);
//		if (i == 4512)
//			printf("\n%d(%s) %d- tr_0 %d tr_1 %d\n", i, graph[0][i].name, graph[0][i].visited, trace->traces_0[i], trace->traces_1[i]);
	}
//	printf("\n!!!\n");
}
