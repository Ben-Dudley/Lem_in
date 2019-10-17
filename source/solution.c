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

void					score_stack_path(t_graph **graph, t_info *info,
										t_trace *trace)
{
	//int				flow;
	int				add_path;

	//flow = 0;

	add_path = find_path(graph, info, trace);
	if (add_path == 0)
		error_message(graph, info, 69);
	while (add_path > 0)
	{
		info->max_flow += add_path;
		//printf("add_path %d ==== %d\n", add_path, info->max_flow);
	//	if (info->max_flow == 5)
	//		exit(0);
		get_path_numbers(graph, info);
	//	print_max(graph,info);
		//for_fix_stack(graph, info);
	//	printf("www\n");
	//	clear_graph(graph, info);
		if (score_stack(graph, info) == info->max_flow - 1 && info->max_flow > 1)
		{
		//	printf("ooo\n");
			info->max_flow--;
			return;
		}
		//add_path = 0;
		add_path = find_path(graph, info, trace);
	}
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

//int					stack_max_flow(t_graph **graph, t_info *info,
//								int index, int flow, int length)
//{
//	t_link			*temp;
//
//	if (flow > info->max_flow)
//		return (1);
//	temp = graph[0][index].link;
//	while (temp)
//	{
//		if (graph[0][temp->node].visited == 0 && temp->node != info->ind_start
//			&& temp->status + temp->reverse->status == 1)
//		{
//			graph[0][temp->node].visited = flow;
//			if (find_link_node(graph, info, temp->node))
//			{
//				if (stack_max_flow(graph, info, info->ind_start, flow + 1, 0))
//					return (1);
//				graph[0][temp->node].visited = 0;
//				return (0);
//			}
//			if (stack_max_flow(graph, info, temp->node, flow, length + 1))
//				return (1);
//			graph[0][temp->node].visited = 0;
//		}
//		temp = temp->next;
//	}
//	return (0);
//}

//int					diff_stack_max(t_graph **graph, t_info *info,
//									t_trace *trace)
//{
////	int				stack;
////
////	stack = score_stack_path(graph, info, trace);
////	// count min flow and path min flow
//////	printf("aaaa\n"); //
//////	;	info->count_ants *= -1
////	info->max_flow = score_stack_path(graph, info, trace);
//////	printf("aaaa\n");
////	return (stack);
//}

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
	score_stack_path(graph, info, &trace);
//	stack = diff_stack_max(graph, info, &trace);
//	printf("stack 0 size %d and max_flow size %d\n", info->count_ants, info->max_flow);
//	if (stack < info->max_flow)
//	{
///		print_max(graph, info);
//stack_max_flow(graph, info, info->ind_start, 1, 0);
//printf("stack %d\n", stack);
//print_massiv(graph, info);
//printf("stack %d\n", stack);
//	clear_graph(graph, info, 1);
//	stack =
//		printf("stack %d", stack);
//	}
//	for_fix_stack(graph, info);
	create_del_trace(&trace, 0, graph, info);
	if (info->max_flow > 0)
		score_ways(graph, info, info->max_flow);
	return (1);
}
