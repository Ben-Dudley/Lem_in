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
										t_trace *trace)
{
	int				count;
	int				add_path;

	count = 0;
	add_path = find_path(graph, info, trace);
	while (add_path > 0)
	{
		count += add_path;
		add_path = find_path(graph, info, trace);
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
									t_trace *trace)
{
	int				stack;

	stack = score_stack_path(graph, info, trace);
	// count min flow and path min flow
	//printf("aaaa\n"); //
	info->count_ants *= -1;
	info->max_flow = score_stack_path(graph, info, trace);
	info->count_ants *= -1;
	return (stack);
}

void				create_del_trace(t_trace *temp,int configuration, t_graph **graph, t_info *info)
{
	if (configuration == 0)
	{
		free(temp->queue);
		free(temp->traces_0);
		free(temp->traces_1);
	}
	if (configuration == 1)
	{
		if (!(temp->queue = (int *)malloc(sizeof(int) * (info->count_node + 1))))
			error_message(graph, info, 0);
		if (!(temp->traces_0 = (int *)malloc(sizeof(int) * (info->count_node + 1))))
			error_message(graph, info, 0);
		if (!(temp->traces_1 = (int *)malloc(sizeof(int) * (info->count_node + 1))))
			error_message(graph, info, 0);
	}
}

int					solution(t_graph **graph, t_info *info)
{
	t_trace			trace;
	int				stack;

	create_del_trace(&trace, 1, graph, info);
	stack = diff_stack_max(graph, info, &trace);

//	printf("stack 0 size %d and max_flow size %d\n", stack, info->max_flow);

//	//if (info->max_flow <= 0) //error delete sluchaino
	print_max(graph, info);
//	//for_fix_stack(graph, info);
	if (stack < info->max_flow)
	{
////		print_max(graph, info);
		//stack_max_flow(graph, info, info->ind_start, 1, 0);
		//get_path_numbers(graph, info);

		//clear_graph(graph, info, 1);
		//stack = score_ants(graph, info, stack);
//		//	printf("stack %d", stack);
	}
	create_del_trace(&trace, 0, graph, info);
	score_ways(graph, info, stack);
	return (1);
}
