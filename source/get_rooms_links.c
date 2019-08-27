/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants_rooms_links.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:52:17 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/21 20:24:09 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/**
 *  Обработать вхождение левых строк
 * 	То, что введен старт и энд
 *	Переписать листы
 *	Разделить
 */
void	get_rooms_links(t_graph **graph, t_info *info)
{
	int flag;
	char *line;
	char *name;
	int i;
	int j;

	flag = 0;
	i = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (*line == '#')
		{
			if (!ft_strcmp("##start\n", line))
			{
				free(line);
				get_next_line(0, &line);
				get_room(graph, info, flag, line);
				info->ind_start = info->count_node;
			}
			else if (!ft_strcmp("##end\n", line))
			{
				free(line);
				get_next_line(0, &line);
				get_room(graph, info, flag, line);
				info->ind_end = info->count_node;
			}
		}
		else if (ft_strchr((const char*)(line), ' ') != NULL)
			get_room(graph, info, flag, line);
		else if (ft_strchr((const char*)(line), '-') != NULL)
		{
		//	printf("1\n");
			flag = 1;
			name = ft_strsub((const char *)(line), 0, ft_strrchr((const char*)(line), '-') - line);
			i = 0;
			while (i < info->count_node)
			{
				if (!ft_strcmp(name, graph[0][i].name))
					break ;
				i++;
			}
			if (i == info->count_node)
				error("Such a room does not exist in the graph. Unable to create path\n", graph, info);
			free(name);
			printf("|%s|\n", graph[0][i].name);
			if (graph[0][i].link == NULL)
				graph[0][i].link = new_links(graph[0], info);
			name = ft_strsub((const char *)(line), (unsigned int)(ft_strrchr((const char*)(line), '-') + 1 - line), line + ft_strlen(line) - ft_strrchr((const char*)(line), '-') - 1);
			j = 0;
			while (j < info->count_node)
			{
				if (!ft_strcmp(name, graph[0][j].name))
					break ;
				j++;
			}
			if (j == info->count_node)
				error("Such a room does not exist in the graph. Unable to create path\n", graph, info);
			free(name);
			if (graph[0][j].link == NULL)
				graph[0][j].link = new_links(graph[0], info);
			graph[0][i].link[j / sizeof(size_t) * 8] = 1 << (j % sizeof(size_t) * 8);
			graph[0][j].link[i / sizeof(size_t) * 8] = 1 << (j % sizeof(size_t) * 8);
		}
		else
			return ; // проверить всё ли зафришино
			//error("Otpravka dal'we\n", graph, info);
		free(line);
	}
}