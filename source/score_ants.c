/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:32:54 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/31 21:13:09 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			reverse_node(t_path **path)
{
	t_node		*ptr;
	t_node		*temp;

	temp = (*path)->node;
	ptr = NULL;
	while (temp->next && temp->next->next)
	{
		temp = temp->next->next;
		((*path)->node)->next->next = (*path)->node;
		((*path)->node) = ((*path)->node)->next;
		((*path)->node)->next->next = ptr;
		ptr = (*path)->node;
		(*path)->node = temp;
	}
	if ((*path)->node->next)
	{
		temp = temp->next;
		temp->next = (*path)->node;
		temp->next->next = ptr;
		(*path)->node = temp;
	}
	else
		(*path)->node->next = ptr;
}

void			reverse_path(t_graph **graph, t_info *info)
{
	t_path *temp;

	temp = info->path;
	while (temp)
	{
		reverse_node(&temp);
		temp = temp->next;
	}
}

void			reverse_list(t_graph **graph, t_info *info)
{
	t_path		*ptr;
	t_path		*temp;

	temp = info->path;
	ptr = NULL;
	while (temp->next && temp->next->next)
	{
		temp = temp->next->next;
		(info->path)->next->next = info->path;
		(info->path) = (info->path)->next;
		(info->path)->next->next = ptr;
		ptr = info->path;
		info->path = temp;
	}
	if (info->path->next)
	{
		temp = temp->next;
		temp->next = info->path;
		temp->next->next = ptr;
		info->path = temp;
	}
	else
		info->path->next = ptr;
}

void			del_flow(t_graph **graph, t_info *info, int count)
{
	t_path		*ptr;
	t_path		*temp;

	ptr = info->path;
	temp = ptr;
	while (ptr)
	{
		if (ptr->stack != count)
		{
			if (temp == ptr)
			{
				info->path = info->path->next;
				temp = info->path;
			}
			else
				temp->next = ptr->next;
			free(ptr);
			ptr = temp;
		}
		else
		{
			temp = ptr;
			ptr = ptr->next;
		}
	}
}

//void			del_flow(t_graph **graph, t_info *info, int count)
//{
//	t_path		*ptr;
//	t_path		*temp;
//	t_path		*temp1;
//	int 		i;
//
//	i = 0;
//	//count = info->max_flow;
//	//ft_print_pyti(graph, info);
//	ptr = info->path;
//	while (ptr)
//	{
//		if (ptr->stack != count)
//		{
//			temp = ptr->next;
//			free(ptr);
//			ptr = temp;
//		}
//		else if (i == 0 && count != info->max_flow)
//		{
//			info->path = ptr;
//			i = 1;
//		}
//		else if (i == 0 && count == info->max_flow)
//			temp1 = ptr;
//		if (ptr)
//			ptr = ptr->next;
//	}
//	if (count == info->max_flow)
//		temp1->next = NULL;
//	ft_print_pyti(graph, info);
//
//}

void 				score_ways(t_graph **graph, t_info *info)
{
	t_path		*ptr;
	int 		count_ways;
	int 		*ways;
	int 		i;
	int 		j;
	int 		score_ants;
	//ft_print_pyti(graph, info);
	reverse_list(graph, info);
	ft_print_pyti(graph, info);
	reverse_path(graph, info);
	ft_print_pyti(graph, info);
	printf("\nbefore count_ants - %d\n", info->count_ants);

	ptr = info->path;
	count_ways = 0;
	score_ants = info->count_ants;
	while (ptr)
	{
		ptr = ptr->next;
		++count_ways;
	}

		if (!(ways = (int *) malloc(sizeof(int) * count_ways)))
			error("MEMEEEE\n", graph, info);
		i = 0;
		while (i < count_ways)
			ways[i++] = 0;
	if (count_ways > 1)
	{
		ptr = info->path;
		i = 0;
		while (score_ants > 0 && i < count_ways - 1)
		{
			j = 0;
			while (j <= i)
			{
				ways[j] += ptr->next->length - ptr->length;
				score_ants -= ways[j];
				++j;
			}
			++i;
		}
		j = 0;
		i =  score_ants / count_ways;
		while (j < count_ways && score_ants > 0)
		{
			ways[j] += i;
			score_ants -= i;
			++j;
		}
		j = 0;
		while (j < count_ways && score_ants > 0)
		{
			ways[j] += 1;
			score_ants -= 1;
			++j;
		}
		print_ways(info, ways, count_ways);
	}
	else
		ways[0] = info->count_ants;

		steps_ants(graph, info, ways, count_ways);
}

void				score_ants(t_graph **graph, t_info *info, int count)
{
	int 		steps;
	int 		length_mf;
	int 		count_ants;
	t_path		*ptr;


//	ft_print_pyti(graph, info);
	ptr = info->path;
	steps = 0;
	length_mf = 0;
	while (ptr)
	{
		if (ptr->stack == info->max_flow)
		{
			length_mf += ptr->length;
			steps += ptr->length;
		}
		else
			steps -= ptr->length;
		ptr = ptr->next;
	}
	if (steps <= 0)
		error("WHAT?????", graph, info);
	count_ants = steps * info->max_flow - length_mf;
	printf("count ants %d and info ants %d mf %d steps %d\n",count_ants, info->count_ants, length_mf, steps);
	if (info->count_ants > count_ants)
	{
		printf("ifs)\n");
		del_flow(graph, info, info->max_flow);
	}

	else
	{
		printf("else)\n");
		//сразу удалить множество макс флов
		del_flow(graph, info, 0);
	}
}

