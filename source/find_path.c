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

static int			init_mass(t_info *info, int *queue, int *traces_0, int *traces_1)
{
	int			i;

	i = 1;
	queue[0] = info->ind_start;
	while (i <= info->count_node)
		queue[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		traces_0[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		traces_1[i++] = -1;
	traces_0[info->ind_start] = info->ind_start;
	traces_1[info->ind_start] = info->ind_start;
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

static int		get_path(t_graph **graph, t_info *info, int *traces_0, int *traces_1,
						int flag)
{
	printf("Save path\n");
	if (flag)
	{
		save_path(graph, info, traces_0, info->ind_end);
		--info->stack->path->length;
		reverse_node(&info->stack->path);
	}
	else
		restoration_path(graph, info, traces_0, traces_1);
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

/*
				 * && (graph[0][traces[queue[i]]].visited == 1) 3
				 * && graph[0][ptr->node].weight > 0 1
				 */

int				find_path(t_graph **graph, t_info *info,
						int *queue, int *traces_0, int *traces_1)
{
	int			i;
	int			j;
	t_link		*ptr;
	int			weight;

	weight = 0;
	int ko;
	ko = -1;
	while (++ko < info->count_node)
		if (graph[0][ko].weight < 0)
			graph[0][ko].weight *= -1;
	i = init_mass(info, queue, traces_0, traces_1);
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

			if (ptr->status != 0 &&
			((graph[0][queue[i]].visited == 0 && traces_0[ptr->node] == -1) ||
			(info->count_ants < 0 && graph[0][queue[i]].visited == 1 && traces_1[ptr->node] == -1 &&
			((graph[0][queue[i]].weight < 0) ||
			(ptr->reverse->status == 0 && graph[0][ptr->node].visited == 1)))))
			{
				printf("%d(%s) ---- %d(%s)\n", graph[0][queue[i]].visited, graph[0][queue[i]].name, graph[0][ptr->node].visited, graph[0][ptr->node].name);
				if (!(traces_0[ptr->node] == -1 && traces_1[ptr->node] == -1)
					&& find_index(info, queue, ptr->node) < 1 && info->count_ants < 0)
				{
					printf("rewrite_queue\n");
					j -= 2;
					i = rewrite_queue(info, queue, i, ptr->node);
				}

				if (info->count_ants < 0 && ptr->status != 0 && ptr->reverse->status == 0 &&
					graph[0][queue[i]].visited == 1 && graph[0][ptr->node].visited == 1 && traces_1[ptr->node] == -1)
				{
					printf("weigth\n");
					if (graph[0][ptr->node].weight > 0)
						graph[0][ptr->node].weight *= -1;
					queue[++j] = ptr->node;
					traces_1[ptr->node] = queue[i];
				}
				else if (traces_0[ptr->node] == -1)
				{
					printf("vis_0\n");
					queue[++j] = ptr->node;
					traces_0[ptr->node] = queue[i];
				}

				if (ptr->node == info->ind_end)
				{
//						if (graph[0][queue[i]].weight < 0)
//						{
//							printf("333\n");
//							graph[0][queue[i]].weight *= -1;
//
//						}
					return (get_path(graph, info, traces_0, traces_1,
									 (info->count_ants > 0) ? 1 : 0));
				}
			}
			ptr = ptr->next;
		}
//		if (graph[0][queue[i]].weight < 0)
//			graph[0][queue[i]].weight *= -1;
//		printf("\n");
	}

	return (0);
}
