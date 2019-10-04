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

void			print_massiv(t_graph **graph, t_info *info)
{
	int			i;
	t_link		*temp;

	i = 0;
	while (i < info->count_node)
	{
		printf(" %d ", graph[0][i].visited);// удалить заменить
		i++;
	}
	i = 0;
	printf("\n");
}

void				get_path_numbers(t_graph **graph, t_info *info)
{
	t_link			*temp;
	t_path			*path;
	int				i;

	i = 0;
	print_massiv(graph, info);
	exit(0);
	while (++i <= info->max_flow)
	{
		temp = graph[0][info->ind_start].link;
		path = new_path(graph, info);
		add_path(&info->path, path);
		add_node(&path->node, new_node(graph, info, info->ind_start));
		//in_stack_add(graph, info, info->path->stack, path);
		path->stack = info->max_flow;
		while (temp && temp->node != info->ind_end)
		{
			if (graph[0][temp->node].visited == i)
			{
				add_node(&path->node, new_node(graph, info, temp->node));
				//graph[0][temp->node].visited *= -1;
				++info->path->length;
				temp = graph[0][temp->node].link;
			}
			else
				temp = temp->next;
		}
		add_node(&path->node, new_node(graph, info, info->ind_end));
	}
}

int					stack_max_flow(t_graph **graph, t_info *info,
						int index, int flow, int length)
{
	t_link			*temp;

	if (flow > info->max_flow)
	{
		print_massiv(graph, info);
		exit(0);
		return (1);
	}
	temp = graph[0][index].link;
	while (temp)
	{
		if (graph[0][temp->node].visited == 0 && temp->node != info->ind_start)
		{
			graph[0][temp->node].visited = flow;
			temp->status = 0;
			temp->reverse->status = 0;
			if (find_link_node(graph, info, temp->node))
			{
				if (stack_max_flow(graph, info, info->ind_start, flow + 1, 0))
					return (1);
				temp->status = 1;
				return (0);
			}
			if (stack_max_flow(graph, info, temp->node, flow, length + 1))
				return (1);
			temp->status = 1;
		}
		temp = temp->next;
	}
	return (0);
}

void			ft_print_pyti(t_graph **graph, t_info *info)
{
	t_path		*temp;
	t_node		*nodo4ka;
	temp = info->path;
	while (temp)
	{
		nodo4ka =  temp->node;
		printf("\nlen - %d, stack - %d \n", temp->length, temp->stack);
		while (nodo4ka)
		{
			printf(" %d - (%s) ", nodo4ka->node, graph[0][nodo4ka->node].name);
			nodo4ka = nodo4ka->next;
		}
		printf(" \n");
		temp = temp->next;
	}
	printf(" \n");
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
	stack = score_stack_path(graph, info, queue, traces);
 	info->count_ants *= -1;
	info->max_flow = score_stack_path(graph, info, queue, traces);
	info->count_ants *= -1;
	printf("stack 0 size %d and max_flow size %d\n", stack, info->max_flow);
	if (info->max_flow <= 0)
		error_message(graph, info, 1); //eto nado&&&
	if (stack < info->max_flow)
	{
		stack_max_flow(graph, info, info->ind_start, 1, 0);
		printf("PO\n");
		get_path_numbers(graph, info);
		printf("PO\n");
		ft_print_pyti(graph, info);
		exit(0);
		clear_graph(graph, info);
		stack = score_ants(graph, info, stack);
	}
	free(queue);
	free(traces);
	score_ways(graph, info, stack);
	return (1);
}
