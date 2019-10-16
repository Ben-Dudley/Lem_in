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

static int			init_mass(t_info *info, t_trace *trace)
{
	int			i;

	i = 1;
	trace->queue[0] = info->ind_start;
	while (i <= info->count_node)
		trace->queue[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		trace->traces_0[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		trace->traces_1[i++] = -1;
	trace->traces_0[info->ind_start] = info->ind_start;
	trace->traces_1[info->ind_start] = info->ind_start;
	return (-1);
}

static int		find_index(t_info *info, t_trace *trace, int node)
{
	int		j;

	j = 0;
	while (j <= info->count_node)
	{
		if (trace->queue[j] == node)
			break ;
		j++;
	}
	return (j);
}

static int		get_path(t_graph **graph, t_info *info, t_trace *trace,
						int flag)
{
//printf("Save path\n");
	if (flag)
	{
		save_path(graph, info, trace, info->ind_end);
		--info->stack->path->length;
		reverse_node(&info->stack->path);
	}
	else
		restoration_path(graph, info, trace);
	return (1);
}

int				rewrite_queue(t_info *info, t_trace *trace, int j, int node)
{
	int i;
//	int count;

	i = 0;
	//count = 0;
	while (trace->queue[i] != node)
		i++;
//	while (i < j - 1)
//	{
//		trace->queue[i] = trace->queue[i + 1];
//		i++;
//	}
//	count = j - 1;
	while (trace->queue[i] != -1)
	{
		trace->queue[i] = trace->queue[i + 1];
		i++;
	}
//	printf("%d -- queue %d\n", i - 2, queue[i - 2]);
	return (j - 1);
}

/*
				 * && (graph[0][traces[queue[i]]].visited == 1) 3
				 * && graph[0][ptr->node].weight > 0 1
				 */

int				find_path(t_graph **graph, t_info *info,
						t_trace *trace)
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
	i = init_mass(info, trace);
	//printf("init\n");
	j = 0;
	while (trace->queue[++i] != -1)
	{
		ptr = graph[0][trace->queue[i]].link;
		if (trace->queue[i] == info->ind_start)
			graph[0][trace->queue[i]].weight = weight;
		if (graph[0][trace->queue[i]].weight == weight)
			weight = weight + 1;
		while (ptr)
		{
			if (weight < graph[0][ptr->node].weight)
			{
				graph[0][ptr->node].weight = weight;
			}

//			if (ft_strcmp("Hlj3", graph[0][trace->queue[i]].name) == 0 || ft_strcmp("Hlj3", graph[0][ptr->node].name) == 0)
//				printf("aueue[i] %d , ptr->node %d tr_0 %d, tr_1 %d, weight %d, %d-%d, status %d, rev %d\n", trace->queue[i], ptr->node, trace->traces_0[ptr->node], trace->traces_1[ptr->node],
//					   graph[0][trace->queue[i]].weight, graph[0][trace->queue[i]].visited, graph[0][ptr->node].visited, ptr->status, ptr->reverse->status);
			if (ptr->status != 0 &&
			((graph[0][trace->queue[i]].visited == 0 && trace->traces_0[ptr->node] == -1) ||
			(info->count_ants < 0 && graph[0][trace->queue[i]].visited == 1 && trace->traces_1[ptr->node] == -1 &&
			((graph[0][trace->queue[i]].weight < 0) ||
			(ptr->reverse->status == 0 && graph[0][ptr->node].visited == 1)))))
			{
//				if (ft_strcmp("Hlj3", graph[0][trace->queue[i]].name) == 0 || ft_strcmp("Hlj3", graph[0][ptr->node].name) == 0)
			printf("%d(%s)(%d) ---- %d(%s)(%d)\n", graph[0][trace->queue[i]].visited, graph[0][trace->queue[i]].name, trace->queue[i], graph[0][ptr->node].visited, graph[0][ptr->node].name, ptr->node);
				if (!(trace->traces_0[ptr->node] == -1 && trace->traces_1[ptr->node] == -1)
					&& find_index(info, trace, ptr->node) < i && info->count_ants < 0)
				{
//					if (ft_strcmp("Hlj3", graph[0][trace->queue[i]].name) == 0 || ft_strcmp("Hlj3", graph[0][ptr->node].name) == 0)
					  printf("rewrite_queue\n");
					j -= 2;
					i = rewrite_queue(info, trace, i, ptr->node);
					printf("j -- %d\n", j);
					printf("%d(%s) ---- %d(%s)\nrewrite\n", graph[0][trace->queue[i]].visited, graph[0][trace->queue[i]].name, graph[0][ptr->node].visited, graph[0][ptr->node].name);
				}

				if (info->count_ants < 0 && ptr->status != 0 && ptr->reverse->status == 0 &&
					graph[0][trace->queue[i]].visited == 1 && graph[0][ptr->node].visited == 1 && trace->traces_1[ptr->node] == -1)
				{
//					if (ft_strcmp("Hlj3", graph[0][trace->queue[i]].name) == 0 || ft_strcmp("Hlj3", graph[0][ptr->node].name) == 0)
					printf("weigth\n");
					if (graph[0][ptr->node].weight > 0)
						graph[0][ptr->node].weight *= -1;
					trace->queue[++j] = ptr->node;
					trace->traces_1[ptr->node] = trace->queue[i];
				}
				else if (trace->traces_0[ptr->node] == -1)
				{
//					if (ft_strcmp("Hlj3", graph[0][trace->queue[i]].name) == 0 || ft_strcmp("Hlj3", graph[0][ptr->node].name) == 0)
					printf("vis_0\n");
					trace->queue[++j] = ptr->node;
					trace->traces_0[ptr->node] = trace->queue[i];
					//printf("%d -- tr_0 %d\n", ptr->node, traces_0[ptr->node]);
				}

				if (ptr->node == info->ind_end)
				{
//						if (graph[0][queue[i]].weight < 0)
//						{
//							printf("333\n");
//							graph[0][queue[i]].weight *= -1;
//
//						}
printf("wwww\n");f
					return (get_path(graph, info, trace,
									 (info->count_ants > 0) ? 1 : 0));
				}
			}
			ptr = ptr->next;
		}
//		if (graph[0][queue[i]].weight < 0)
//			graph[0][queue[i]].weight *= -1;
		printf("\n");
	}
	printf("qqq\n");
	return (0);
}
