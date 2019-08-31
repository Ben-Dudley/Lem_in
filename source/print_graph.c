/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 17:24:18 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/31 18:18:11 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		printf(" \n ");
		temp = temp->next;
	}
	printf(" \n ");
}

void			ft_print_massiv(t_graph **graph, t_info *info)
{
	int			i;
	t_link		*temp;

	i = 0;
	printf("ants - %d\n", info->count_ants); /*удалить*/
	while (i < info->count_node)
	{
		printf("%s\n", graph[0][i++].name);// удалить заменить
	}
	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			printf("%s-%s\n", graph[0][i].name, graph[0][temp->node].name);
/*удалить заменитть*/ 
			temp = temp->next; // убрать двойной вывод или как то так
		}
		++i;
	}
	if (info->ind_start != -1)
		printf("start %s\n", graph[0][info->ind_start].name); /*удалить*/
	if (info->ind_end != -1)
		printf("end %s\n", graph[0][info->ind_end].name); /*удалить*/
}

void			print_massiv(t_graph **graph, t_info *info)
{
	int			i;
	t_link		*temp;

	i = 0;
	while (i < info->count_node)
	{
		printf(" %d ", graph[0][i++].visited);// удалить заменить
	}
	i = 0;
	printf("\n");
	while (i <= info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			printf("(%s-%s - ", graph[0][i].name, graph[0][temp->node].name);
			printf("%d) ", temp->status);
/*удалить заменитть*/
			temp = temp->next; // убрать двойной вывод или как то так
		}
		++i;
	}
	printf("\n");
//	if (info->ind_start != -1)
//		printf("start %s\n", graph[0][info->ind_start].name); /*удалить*/
//	if (info->ind_end != -1)
//		printf("end %s\n", graph[0][info->ind_end].name); /*удалить*/
}