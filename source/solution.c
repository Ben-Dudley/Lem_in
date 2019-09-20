/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:11:16 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/20 08:50:46 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	clear_graph(graph, info);
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

void				get_path_numbers(t_graph **graph, t_info *info)
{
	t_link			*temp;
	t_path			*path;
	int				i;

	i = 0;
	while (++i <= info->max_flow)
	{
		temp = graph[0][info->ind_start].link;
		path = new_path(graph, info);
		add_path(&info->path, path);
		add_node(&path->node, new_node(graph, info, info->ind_start));
		path->stack = info->max_flow;
		while (temp && temp->node != info->ind_end)
		{
			if (graph[0][temp->node].visited == i)
			{
				add_node(&path->node, new_node(graph, info, temp->node));
				++info->path->length;
				temp = graph[0][temp->node].link;
			}
			else
				temp = temp->next;
		}
		add_node(&path->node, new_node(graph, info, info->ind_end));
	}
}

void			ft_print_pyti(t_graph **graph, t_info *info)
{
	t_path		*temp;
	t_node		*nodo4ka;
	temp = info->path;
	while (temp)
	{
		nodo4ka =  temp->node;
		if (temp->stack == info->max_flow)
		{
		printf("\nlen - %d, stack - %d \n", temp->length, temp->stack);
		while (nodo4ka)
		{
			printf(" %d - (%s) ", nodo4ka->node, graph[0][nodo4ka->node].name);
			nodo4ka = nodo4ka->next;
		}
		printf(" \n ");
		}
		temp = temp->next;
	}
	if (temp && temp->stack == info->max_flow)
		printf(" \n ");
}

int					stack_max_flow(t_graph **graph, t_info *info,
						int index, int flow)
{
	t_link			*temp;

	if (flow > info->max_flow)
		return (1);
	temp = graph[0][index].link;
	printf("info->ind_start %d\n", flow);
	while (temp)
	{
		//printf("2stack_max_flow\n");
		if (graph[0][temp->node].visited == 0 && temp->node != info->ind_start)
		{// проверить ребра
			graph[0][temp->node].visited = flow;
			//printf("3stack_max_flow\n");
			if (find_link_node(graph, info, temp->node))
			{
				//printf("!!!!!!!!!!!stack_max_flow\n");
				if (stack_max_flow(graph, info, info->ind_start, flow + 1))
					return (1);
				graph[0][temp->node].visited = 0;
				return (0);
			}
		//	printf("4stack_max_flow\n");
			if (stack_max_flow(graph, info, temp->node, flow))
				return (1);
			graph[0][temp->node].visited = 0;
		}
		temp = temp->next;
		//printf("5stack_max_flow\n");
	}
	return (0);
}

int					solution(t_graph **graph, t_info *info)
{
	int				*queue;
	int				*traces;
	int				stack;

	if (!(queue = (int *)malloc(+sizeof(int) * (info->count_node + 1))))
		error_message(graph, info, 0);
	if (!(traces = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error_message(graph, info, 0);
	stack = score_stack_path(graph, info, queue, traces);
	info->count_ants *= -1;
	info->max_flow = score_stack_path(graph, info, queue, traces);
	info->count_ants *= -1;
	if (info->max_flow <= 0)
		error_message(graph, info, 1);
	printf("1solution\n");
	if (stack < info->max_flow)
	{
		stack_max_flow(graph, info, info->ind_start, 1);
		printf("2solution\n");
		get_path_numbers(graph, info);
//	printf("3solution\n");
		clear_graph(graph, info);
//		printf("4solution\n");
		stack = score_ants(graph, info, stack);
//	printf("5solution\n");
	}
//	printf("6solution\n");
	free(queue);
	free(traces);
	score_ways(graph, info, stack);
//	printf("7solution\n");
	return (1);
}
