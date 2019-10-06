/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:09:50 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/05 19:42:16 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Here is search shortest paths stack.
** Here is also counts the numbers max flow.
*/

static int		init_mass(t_info *info, int *queue, int *traces)
{
	int			i;

	i = 1;
	queue[0] = info->ind_start;
	while (i <= info->count_node)
		queue[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		traces[i++] = -1;
	return (-1);
}

static int		find_index(t_info *info, int *queue, int node)
{
	int		j;

	j = 0;
	while (j <= info->count_node)
	{
		if (queue[j] == node)
			break ;
		j++;
	}
	return (j);
}

static int		get_path(t_graph **graph, t_info *info, int *traces,
						int flag)
{
	if (flag)
	{
		save_path(graph, info, traces, info->ind_end);
		--info->stack->path->length;
		reverse_node(&info->stack->path);
	}
	else
		restoration_path(graph, info, traces);
	return (1);
}

int				rewrite_queue(t_info *info, int *queue, int j, int node)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (queue[i] != node)
		i++;
	while (i < j - 1)
	{
		queue[i] = queue[i + 1];
		i++;
	}
	count = j - 1;
	while (queue[i] != -1)
	{
		queue[i] = queue[i + 2];
		i++;
	}
	return (count);
}

int				find_path(t_graph **graph, t_info *info,
						int *queue, int *traces)
{
	int			i;
	int			j;
	t_link		*ptr;
	int			weight;

	weight = 0;
	i = init_mass(info, queue, traces);
	j = 0;
	while (queue[++i] != -1)
	{
		ptr = graph[0][queue[i]].link;
		if (queue[i] == info->ind_start)
			graph[0][queue[i]].weight = weight;
		if (graph[0][queue[i]].weight == weight)
			weight = weight + 1;
		while (ptr)
		{
			if (weight < graph[0][ptr->node].weight)
			{
				graph[0][ptr->node].weight = weight;
			}
//			printf("queue[%d] %s(%d)\n",i, graph[0][queue[i]].name, graph[0][queue[i]].visited);
//			printf("ptr->node %s (%d, %d)\n", graph[0][ptr->node].name, ptr->status, ptr->reverse->status);
//			if ()
//			{
//				graph[0][queue[i]].visited = 0;
//				graph[0][ptr->node].visited = 0;
//			}
		//	printf("%s %s\n", graph[0][queue[i]].name, graph[0][ptr->node].name);
			if ((ptr->status != 0 && (graph[0][queue[i]].visited == 0 ||
			graph[0][queue[i]].weight < 0))|| (info->count_ants < 0 && ptr->status != 0 && ptr->reverse->status == 0 &&
			graph[0][queue[i]].visited == 1 && graph[0][ptr->node].visited == 1))
			{
				if (info->count_ants < 0 && ptr->status != 0 && ptr->reverse->status == 0 &&
					graph[0][queue[i]].visited == 1 && graph[0][ptr->node].visited == 1)
				{
					//printf("!!!!!!!!%s", graph[0][ptr->node].name);
					graph[0][ptr->node].weight *= -1;
					j = -2;
					i = rewrite_queue(info, queue, i, ptr->node);
					queue[++j] = ptr->node;
					traces[ptr->node] = queue[i];
					break ;
					//перезаписать все вершины без вершины которая с минимальным весом
					//и текующую начать с начала
				}
				//	printf("%s %s\n", graph[0][queue[i]].name, graph[0][ptr->node].name);
				 if (find_index(info, queue, ptr->node) == info->count_node + 1)
				{
					//printf("ddd\n");
					//printf("%s %s\n", graph[0][queue[i]].name, graph[0][ptr->node].name);
					queue[++j] = ptr->node;
					traces[ptr->node] = queue[i];
					if (ptr->node == info->ind_end)
					{
						if (graph[0][queue[i]].weight < 0)
						{
							printf("333\n");
							graph[0][queue[i]].weight *= -1;

						}
						return (get_path(graph, info, traces,
										 (info->count_ants > 0) ? 1 : 0));
					}
				}
			}
			ptr = ptr->next;
		}
		if (graph[0][queue[i]].weight < 0)
			graph[0][queue[i]].weight *= -1;
//		printf("\n");
	}

	return (0);
}
