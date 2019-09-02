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

void        print_room(t_graph **graph, t_info *info, int count, int score_ants)
{
	t_path *temp;
	t_node *temp_node;
	int 	i;
	int 	ZV;

	i = 0;
	while (i < count)
	{
		ZV = i;
		temp = info->path;
		while (temp)
		{
			//printf("Zenya\n");
			temp_node = temp->node;
			while (temp_node)
			{
				//printf("%dTRTRTR%d\n", i, temp_node->ant);
				if (i == temp_node->ant)
				{
					if (temp_node->ant)
					printf("L%d-%s ", temp_node->ant, graph[0][temp_node->node].name); //delete and space
					++i;
				}
				temp_node = temp_node->next;
			}
			temp = temp->next;
		}
		if (ZV == i)
			i++;
	}
	printf("\n");
}

void			steps_ants(t_graph **graph, t_info *info, int *ways, int count_ways)
{
	t_node *ptr_node;
	t_path *ptr_path;
	int j;
	int i;
	int score_ants;

	j = 1;
	score_ants = 0;
	//print_ways(info, ways, count_ways);
	while (score_ants < info->count_ants)
	{
		i = 0;
		ptr_path = info->path;
		while (ptr_path)
		{
			//printf("L1\n");
			ptr_node = ptr_path->node;
			if (ptr_node->node && !ptr_node->next->node)
				score_ants += 1;
			while (ptr_node->next->node != info->ind_start)
				{
					//printf("L2\n");
					ptr_node->ant = ptr_node->next->ant;
					if (ptr_node->node == info->ind_end && ptr_node->next->ant != 0)
						score_ants += 1;
					ptr_node = ptr_node->next;
				}
			//printf("ways[i] %d - %d\n", ways[i], i);
			if (ways[i] > 0)
			{
				//printf("L3\n");
				ptr_node->ant = j;
				j++;
				ways[i] -= 1;
			}
			else
				ptr_node->ant = 0;
			++i;
			//printf("L4\n");
			ptr_path = ptr_path->next;
		}
		//printf("L score_ants - %d j-%d    info->count_ants- %d\n ", score_ants, j,  info->count_ants);
		print_room(graph, info, j, score_ants);
	}
}

void			print_ways(t_info *info, int *ways, int count)
{
	int i;

	i = 0;
	//printf("after count_ants - %d\n", info->count_ants);
	while (i < count)
	{
		printf(" %d ", ways[i]);
		++i;
	}
	printf("\n");
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
	printf("%d\n", info->count_ants); /*удалить*/
	while (i < info->count_node)
	{
		printf("%s %d %d\n", graph[0][i].name, graph[0][i].x, graph[0][i].y);// удалить заменить
		i++;
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
	printf("\n");
}