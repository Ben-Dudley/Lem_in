/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:32:54 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/31 19:45:12 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int 				score_ways(t_graph **graph, t_info *info)
{
	int 		steps;
	int 		length_mf;
	int 		count_ants;
	t_path		*ptr;


	//ft_print_pyti(graph, info);
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

