/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fordfalkerson.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:21:56 by hharrold          #+#    #+#             */
/*   Updated: 2019/10/17 18:22:00 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				algorithm(t_graph **graph, t_link *ptr,
											t_trace *trace, int *ij)
{
	if (visited_on_node(graph, ptr, trace, ij[0]))
	{
		if (graph[0][ptr->node].weight > 0)
			graph[0][ptr->node].weight *= -1;
		(trace->queue)[++(ij[1])] = ptr->node;
		(trace->traces_1)[ptr->node] = (trace->queue)[ij[0]];
	}
	else if ((trace->traces_0)[ptr->node] == -1)
	{
		(trace->queue)[++(ij[1])] = ptr->node;
		(trace->traces_0)[ptr->node] = (trace->queue)[ij[0]];
	}
	return (ij[1]);
}

int				not_node(t_info *info, t_link *ptr, t_trace *trace, int i)
{
	if (!((trace->traces_0)[ptr->node] == -1
		&& (trace->traces_1)[ptr->node] == -1)
		&& find_index(info, trace, ptr->node) < i)
		return (1);
	return (0);
}

int				visited_on_node(t_graph **graph, t_link *ptr,
											t_trace *trace, int i)
{
	if (ptr->status != 0
		&& ptr->reverse->status == 0
		&& graph[0][(trace->queue)[i]].visited == 1
		&& graph[0][ptr->node].visited == 1
		&& (trace->traces_1)[ptr->node] == -1)
		return (1);
	return (0);
}

int				clear_end_link_weight(t_graph **graph,
							t_info *info, t_trace *trace)
{
	t_link		*ptr;
	int			i;
	int			flag;

	i = -1;
	while (++i < info->count_node)
	{
		graph[0][i].weight = 1;
		flag = 0;
		ptr = graph[0][i].link;
		while (ptr)
		{
			if (ptr->reverse->status == -7)
				ptr->reverse->status = 0;
			if (ptr->status + ptr->reverse->status == 1)
				flag = 1;
			ptr = ptr->next;
		}
		if (flag == 0)
			graph[0][i].visited = 0;
	}
	return (0);
}

int				check_visited(t_graph **graph, t_link *ptr,
										t_trace *trace, int i)
{
	if (ptr->status != 0 && (trace->traces_0)[(trace->queue)[i]]
	!= ptr->node && (trace->traces_1)[(trace->queue)[i]]
	!= ptr->node && ((graph[0][(trace->queue)[i]].visited == 0
	&& (trace->traces_0)[ptr->node] == -1)
	|| (graph[0][(trace->queue)[i]].visited == 1
	&& (trace->traces_1)[ptr->node] == -1
	&& ((graph[0][(trace->queue)[i]].weight < 0)
	|| (ptr->reverse->status == 0 && graph[0][ptr->node].visited == 1)))))
		return (1);
	return (0);
}
