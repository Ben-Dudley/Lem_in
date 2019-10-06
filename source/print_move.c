/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 09:55:56 by hharrold          #+#    #+#             */
/*   Updated: 2019/10/06 09:56:00 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		sup_print_move(t_info *info)
{
	print_buf(info, "\n");
	if (info->flag_score > 0)
		info->flag_score += 1;
	info->count_max_node *= -1;
}

void			print_move(t_graph **graph, t_info *info, int count,
																int count_ways)
{
	t_path		*temp;
	t_node		*temp_node;
	int			i;
	int			counter;

	i = min_score_ants(info, count, count_ways);
	while (i < count)
	{
		counter = i;
		temp = info->stack->path;
		while (temp)
		{
			temp_node = temp->node;
			while (temp_node)
			{
				i += send_to_print_steps(temp_node, i, info, graph);
				temp_node = temp_node->next;
			}
			temp = temp->next;
		}
		if (counter == i)
			i++;
	}
	sup_print_move(info);
}
