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

void				print_max(t_graph **graph, t_info *info)
{
	t_link  *temp;
	int		i;

	i = 0;
	while (i < info->count_node)
	{
		//printf("%d\n", i);
		temp = graph[0][i].link;
		while (temp)
		{
			if (temp->status + temp->reverse->status == 0)
			{
				printf("vertics %s and %s in flow %d, status (%d, %d)\n", graph[0][i].name, graph[0][temp->node].name, graph[0][i].visited, temp->status, temp->reverse->status);
			}
			temp = temp->next;
		}
		i++;
	}
}

int					score_stack_path(t_graph **graph, t_info *info,
										int *queue, int *traces)
{
	int				count;
	int				add_path;
	count = 0;
	add_path = find_path(graph, info, queue, traces);
	while (add_path > 0)
	{
//		if (count >= 8)
//		{
//			print_max(graph, info);
//			printf("\n\n");
//		}
		count += add_path;
		add_path = find_path(graph, info, queue, traces);
	}
//	print_max(graph, info);
	//printf("\n\n");
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

void				print_massiv(t_graph **graph, t_info *info)
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
	while (++i <= info->max_flow)
	{
		temp = graph[0][info->ind_start].link;
		path = new_path(graph, info);
		if (info->stack->stack != info->max_flow)
			add_stack(&info->stack, new_stack(graph, info, info->max_flow, path)); // stack = 0 ???
		else
			add_path(&info->stack->path, path);
		add_node(&path->node, new_node(graph, info, info->ind_start));
		while (temp && temp->node != info->ind_end)
		{
			if (graph[0][temp->node].visited == i) // i  || temp->node == info->ind_start
			{
				add_node(&path->node, new_node(graph, info, temp->node));
				++path->length;
				temp = graph[0][temp->node].link;
			}
			else
				temp = temp->next;
		}
		add_node(&path->node, new_node(graph, info, info->ind_end));
	}

}

void				ft_print_pyti(t_graph **graph, t_info *info)
{
	t_stack		*temp;
	t_node		*nodo4ka;

	temp = info->stack;
	while (temp->path)
	{
		nodo4ka =  temp->path->node;
		printf("\nlen - %d, stack - %d \n", temp->path->length, temp->stack);
		while (nodo4ka)
		{
			printf(" %d - (%s) ", nodo4ka->node, graph[0][nodo4ka->node].name);
			nodo4ka = nodo4ka->next;
		}
		printf(" \n ");
		temp = temp->next;
	}
	if (temp->path && temp->stack == info->max_flow)
		printf(" \n ");
}

void				for_fix_stack(t_graph **graph, t_info *info)
{
	t_stack		*st;
	t_path		*temp;
	t_node		*nodo4ka;

	st = info->stack;
	while (st)
	{
		printf("\nStack#%d ", st->stack);
		temp = st->path;
		while (temp)
		{
			printf("len path %d, ", temp->length);
//			nodo4ka = temp->node;
//			while (nodo4ka)
//			{
//				printf(" %d - (%s) ", nodo4ka->node, graph[0][nodo4ka->node].name);	nodo4ka = nodo4ka->next;
//			}
			temp = temp->next;
		}
		st = st->next;
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

void				print_stack(t_graph **graph, t_info *info)
{
	t_stack		*st;
	t_path		*temp;
	t_node		*nodo4ka;

	st = info->stack;
	while (st)
	{
		temp = st->path;
		while (temp)
		{
			nodo4ka =  temp->node;
			printf("длина пути %d, стек № %d \n", temp->length, st->stack);
			while (nodo4ka)
			{
				printf(" %d - (%s) ", nodo4ka->node, graph[0][nodo4ka->node].name);
				nodo4ka = nodo4ka->next;
			}
			printf(" \n ");
			temp = temp->next;
		}
//		if (temp->path && temp->stack == info->max_flow)
			printf(" \n ");
		st = st->next;
	}
}

void				print_links(t_graph **graph, t_info *info)
{
	int 	i;
	t_link	*temp;

	i = 0;
	while(i < info->count_node)
	{
		temp = graph[0][i].link;
		while(temp)
		{
			printf(" (%s) %d ", graph[0][temp->node].name, graph[0][temp->node].weight);
			temp = temp->next;
		}
		i += 1;
		printf(" \n");
	}
	printf(" \n");
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
			//printf("length %d\n", length);
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

int					solution(t_graph **graph, t_info *info)
{
	int				*queue;
	int				*traces;
	int				stack;
	if (!(queue = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error_message(graph, info, 0);
	if (!(traces = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error_message(graph, info, 0);
	stack = score_stack_path(graph, info, queue, traces); // count min flow and path min flow
	//printf("aaaa\n");
 	info->count_ants *= -1;
	info->max_flow = score_stack_path(graph, info, queue, traces);
	info->count_ants *= -1;
	printf("stack 0 size %d and max_flow size %d\n", stack, info->max_flow);
	//if (info->max_flow <= 0) //error delete sluchaino
	if (stack < info->max_flow)
	{
		print_max(graph, info);
		printf("PK\n");
		stack_max_flow(graph, info, info->ind_start, 1, 0);
		printf("PK\n");
			get_path_numbers(graph, info);
		//for_fix_stack(graph, info);
			clear_graph(graph, info, 1);
			stack = score_ants(graph, info, stack);
		//	printf("stack %d", stack);
	}
	free(queue);
	free(traces);
//	score_ways(graph, info, stack);
	return (1);
}
