/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 17:24:18 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/27 17:24:21 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
