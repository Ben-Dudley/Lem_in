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

static int		search_index(char *name, t_graph **graph, t_info *info)
{
	int		i;

	i = 0;
	while (i < info->count_node)
	{
		if (!ft_strcmp(name, graph[0][i].name))
			break ;
		++i;
	}
	if (i == info->count_node)
		error("Such a room does not exist in the graph. Unable\
		to create path\n", graph, info);
	return (i);
}

static int		help_link(t_graph **graph, t_info *info, char *line)
{
	char			*name;
	int				i;
	int				j;

	name = ft_strsub((const char *)(line), 0,
							ft_strrchr((const char*)(line), '-') - line);
	i = search_index(name, graph, info);
	free(name);
	add_link(&graph[0][i].link, new_link(graph, info));
	name = ft_strsub((const char *)(line),
			(unsigned int)(ft_strrchr((const char*)(line), '-') + 1 - line),
			line + ft_strlen(line) - ft_strrchr((const char*)(line), '-') - 1);
	j = search_index(name, graph, info);
	add_link(&graph[0][j].link, new_link(graph, info));
	free(name);
	(graph[0][j].link)->node = i;
	(graph[0][j].link)->reverse = graph[0][i].link;
	(graph[0][i].link)->reverse = graph[0][j].link;
	(graph[0][i].link)->node = j;
	return (1);
}

int				help_rooms(t_graph **graph, t_info *info, int flag,
																	char *line)
{
	if (!ft_strcmp("##start", line) && flag != 1)
	{
		if (flag > 1)
			error("Insufficient data for processing\n", graph, info);
		return (2);
	}
	else if (!ft_strcmp("##end", line) && flag != 1)
	{
		if (flag > 1)
			error("Insufficient data for processing\n", graph, info);
		return (3);
	}
	else if (flag == 2)
	{
		info->ind_start = info->count_node;
		return (0);
	}
	else if (flag == 3)
	{
		info->ind_end = info->count_node;
		return (0);
	}
	if (flag == 1)
		return (1);
	return (0);
}

void			get_rooms_links(t_graph **graph, t_info *info)
{
	int			flag;
	char		*line;

	flag = 0;
	while (get_next_line(0, &line) > 0)
	{
		//printf("POPOPO\n");
		if (*line == '#')
			flag = help_rooms(graph, info, flag, line);
		else if (ft_strchr((const char*)(line), ' ') != NULL && flag != 1)
			get_room(graph, info, &flag, line);
		else if (ft_strchr((const char*)(line), '-') != NULL)
		{
			if (flag > 1 || info->ind_start == -1 || info->ind_end == -1)
				error("Insufficient data for processing\n", graph, info);
			flag = help_link(graph, info, line);
		}
		else
		{
			if (line)
				free(line); // почистить гнл
			ft_putstr("Otpravka dal'we\n"); // удалим
			break ;
		}
		free(line);
	}
}
/**
 *  Обработать вхождение левых строк
 * 	То, что введен старт и энд
 */