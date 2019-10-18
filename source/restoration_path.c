/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restoration_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:15:40 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/04 16:20:44 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	was_in_room_1(t_graph **graph, t_link *temp, t_trace *trace, int i)
{
	if (((trace->traces_1)[(trace->traces_0)[i]] != -1
			&& temp->status + temp->reverse->status == 1
			&& graph[0][(trace->traces_0)[i]].visited == 1)
			|| trace->traces_0[trace->traces_0[i]] == -1)
		return (1);
	return (0);
}

int			restoration_path(t_graph **graph, t_info *info, t_trace *trace)
{
	int			i;
	t_link		*temp;

	i = info->ind_end;
	while (i != info->ind_start)
	{
		temp = graph[0][(trace->traces_0)[i]].link;
		while (temp)
		{
			if (temp->node == i)
			{
				temp->status = 0;
				if (was_in_room_1(graph, temp, trace, i))
					(trace->traces_0)[(trace->traces_0)[i]] =
							(trace->traces_1)[(trace->traces_0)[i]];
				if ((trace->traces_0)[i] != info->ind_start)
					graph[0][(trace->traces_0)[i]].visited = 1;
				break ;
			}
			temp = temp->next;
		}
		i = (trace->traces_0)[i];
	}
	return (1);
}
