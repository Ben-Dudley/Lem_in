/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:11:04 by hharrold          #+#    #+#             */
/*   Updated: 2019/10/06 15:11:51 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_queue(t_graph **graph, int *queue, int count) // 1
{
	int i;

	i = 0;
	while (i < count)
	{
		printf(" %d(%d) ", queue[i], i);
		++i;
	}
	printf("\n");
}

void				print_max(t_graph **graph, t_info *info) // 1
{
	t_link	*temp;
	int		i;

	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			if (temp->status + temp->reverse->status == 0)
			{
				printf("vertics %s and %s in flow %d, status (%d, %d)\n",
					   graph[0][i].name, graph[0][temp->node].name,
					   graph[0][i].visited, temp->status,
					   temp->reverse->status);
			}
			temp = temp->next;
		}
		i++;
	}
}

void				print_massiv(t_graph **graph, t_info *info) //2
{
	int			i;
	t_link		*temp;

	i = 0;
	while (i < info->count_node)
	{
		printf(" %d ", graph[0][i].visited);
		i++;
	}
	i = 0;
	printf("\n");
}

void				ft_print_pyti(t_graph **graph, t_info *info) // 3
{
	t_stack		*temp;
	t_node		*nodo4ka;

	temp = info->stack;
	while (temp->path)
	{
		nodo4ka = temp->path->node;
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

void				for_fix_stack(t_graph **graph, t_info *info) // 4
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
			nodo4ka = temp->node;
			while (nodo4ka)
			{
				printf(" %d - (%s) ", nodo4ka->node,
						graph[0][nodo4ka->node].name);
				nodo4ka = nodo4ka->next;
			}
			temp = temp->next;
			printf("\n");
		}
		st = st->next;
	}
	printf("\n");
}

void				print_stack(t_graph **graph, t_info *info) // 5
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
			nodo4ka = temp->node;
			printf("длина пути %d, стек № %d \n", temp->length, st->stack);
			while (nodo4ka)
			{
				printf(" %d - (%s) ", nodo4ka->node,
					   graph[0][nodo4ka->node].name);
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

void				print_links(t_graph **graph, t_info *info) // 6
{
	int		i;
	t_link	*temp;

	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			printf(" (%s) %d ", graph[0][temp->node].name,
				   graph[0][temp->node].weight);
			temp = temp->next;
		}
		i += 1;
		printf(" \n");
	}
	printf(" \n");
}


void		print_ways(t_info *info, int *ways, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		printf(" %d ", ways[i]);
		++i;
	}
	printf("\n");
}

//int					stack_max_flow(t_graph **graph, t_info *info,
//									  int index, int flow, int length)
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