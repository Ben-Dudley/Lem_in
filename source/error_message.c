/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:33:37 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/02 15:33:41 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_path(t_path *path)
{
	t_path		*temp;
	t_node		*ptr;

	while (path)
	{
		temp = path->next;
		while (path->node)
		{
			ptr = path->node->next;
			free (path->node);
			path->node = ptr;
		}
		free (path);
		path = temp;
	}
}

static void		free_graph(t_graph **graph, t_info *info)
{
    int		i;
    t_link	*temp;

    i = 0;
    while (i < info->count_node) // (ну типо колличество графов)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			temp = graph[0][i].link->next;
			free (graph[0][i].link);
			graph[0][i].link = temp->next;
		}	
		free (graph[0][i]); // фришится или нет надо ли
		++i;
	}
	free_path(info->path);
	free (info);  // надо ли фришится или нет
}

int				error_message(t_graph **graph, t_info *info, int code_error)
{
	if (code_error == 0)
		ft_printf("Memory allocation error\n");
	if (code_error == 1)
		ft_printf("It is impossible to translate ants\n");
	if (code_error == 2)
		ft_printf("Insufficient data for processing\n");
	if (code_error == 3)
		ft_printf("Such a room does not exist in the graph. Unable\
		to create path\n");
	if (code_error > 3) // типо когда мы получили ant комнаты и связи ,
	{ //но чтото не валидно - мы проверяем на достаточное колличество данных
		if (!solution(graph, info))
		{
			if (code_error == 7)
				ft_printf("It is impossible to translate ants\n");
		}
	}
	free_graph(graph, info);
	return (0); // exit????
}