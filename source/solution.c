/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:11:16 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/20 20:50:10 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "lem_in.h"

/*
** Solution determine which option this better,
** find stack max flow path and shortest path stack.
** It choose best variant and move ants.
** Here also is search paths max flow stack.
*/

int					score_stack_path(t_graph **graph, t_info *info,
										int *queue, int *traces)
{
	int				count;
	int				add_path;

	count = 0;
	add_path = find_path(graph, info, queue, traces);
	while (add_path > 0)
	{
		count += add_path;
		add_path = find_path(graph, info, queue, traces);
	}
	clear_graph(graph, info, info->count_ants > 0 ? 1 : 0);
	return (count);
}

int					find_link_node(t_graph **graph, t_info *info, int node)
{
	t_link			*temp;

	temp = graph[0][info->ind_end].link;
	while (temp)
	{
		if (temp->node == node)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int					stack_max_flow(t_graph **graph, t_info *info,
								int index, int flow, int length)
{
	t_link			*temp;

	if (flow > info->max_flow)
		return (1);
	temp = graph[0][index].link;
	while (temp)
	{
		if (graph[0][temp->node].visited == 0 && temp->node != info->ind_start
			&& temp->status + temp->reverse->status == 1)
		{
			graph[0][temp->node].visited = flow;
			if (find_link_node(graph, info, temp->node))
			{
				if (stack_max_flow(graph, info, info->ind_start, flow + 1, 0))
					return (1);
				graph[0][temp->node].visited = 0;
				return (0);
			}
			if (stack_max_flow(graph, info, temp->node, flow, length + 1))
				return (1);
			graph[0][temp->node].visited = 0;
		}
		temp = temp->next;
	}
	return (0);
}

int					diff_stack_max(t_graph **graph, t_info *info,
									int *queue, int *traces)
{
	int				stack;

	stack = score_stack_path(graph, info, queue, traces);
	// count min flow and path min flow
//	printf("aaaa\n"); //
	info->count_ants *= -1;
	info->max_flow = score_stack_path(graph, info, queue, traces);
	info->count_ants *= -1;
	return (stack);
}

int					solution(t_graph **graph, t_info *info)
{
	int				*queue;
	int				*traces;
	int				stack;

	if (!(queue = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error_message(graph, info, 0);
	if (!(traces = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error_message(graph, info, 0);
	stack = diff_stack_max(graph, info, queue, traces);
	printf("stack 0 size %d and max_flow size %d\n", stack, info->max_flow);
	//if (info->max_flow <= 0) //error delete sluchaino
	if (stack < info->max_flow)
	{
		print_max(graph, info);
		stack_max_flow(graph, info, info->ind_start, 1, 0);
		get_path_numbers(graph, info);
		//for_fix_stack(graph, info);
		clear_graph(graph, info, 1);
		stack = score_ants(graph, info, stack);
		//	printf("stack %d", stack);
	}
	free(queue);
	free(traces);
	score_ways(graph, info, stack);
	return (1);
}
