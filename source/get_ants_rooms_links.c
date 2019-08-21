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

int			put_number(char *str, t_graph **graph, t_info *info)
{
	int	number;
	int	flag;
	int	off;
	int	lim;

	number = 0;
	flag = 1;
	if (*str == '-' || *str == '+')
		flag = (*str++ == '-') ? -1 : 1;
	if (*str == '\0')
		error("You entered nothing\n", graph, info);
	off = flag == 1 ? INT_MAX : INT_MIN;
	lim = flag * (off % 10);
	off /= flag * 10;
	while (*str != '\0')
	{
		if (*str > '9' || *str < '0' || number * flag > off
			|| (flag * number == off && (*str - '0') > lim))
			error("You want to enter a number of type integer\n", graph, info);
		number = number * 10 + flag * (*str - '0');
		str++;
	}
	return (number);
}

void	get_ants(t_graph **graph, t_info *info)
{
	char *line;

	while (get_next_line(0, &line, 0) > 0)
	{
		if (*line == '#' && *(line + 1) != '#')
			continue ;
		else if (ft_isdigit(*line))
		{
			info->count_ants = put_number(line, graph, info);
			free(line);
			if (info->count_ants < 0)
				error("The number of ants can only be positive\n", graph, info);
			return ;
		}
		else
			error("First you need to enter the number of ants\n", graph, info);
		free(line);
	}
}

void		get_room(t_graph **graph, t_info *info, int flag, char *line)
{
	char *name;
	char *name_copy;
	t_graph *node;
	int i;

	i = 0;
	if (flag == 1)
		error("First you need to enter all the vertices, and only then links\n", graph, info);
	if (*line == 'L' || *line == '#')
		error("The vertex name cannot start with characters '#' and 'L'\n", graph, info);
	if (info->count_node >= info->count_max_node || info->count_node == 0)
		*graph = new_graph(*graph, info);
	name = ft_strsub((const char *)(line), (unsigned int)(ft_strrchr((const char*)(line), ' ') + 1 - line) , line + ft_strlen(line) - ft_strrchr((const char*)(line), ' ') - 1);
	graph[info->count_node]->y = put_number(name, graph, info);
	free(name);
	name = ft_strsub((const char *)(line), 0, ft_strrchr((const char*)(line), ' ') - line);
	name_copy = ft_strsub((const char *)(name), (unsigned int)(ft_strrchr((const char*)(name), ' ') + 1 - name), name + ft_strlen(name) - ft_strrchr((const char*)(name), ' ') - 1);
	graph[info->count_node]->x = put_number(name_copy, graph, info);
	free(name_copy);
	name_copy = ft_strsub((const char *)(name), 0,  ft_strrchr((const char*)(name), ' ') - name);
	graph[info->count_node]->name = name_copy;
	free(name);
	while (i < info->count_node)
	{
		if (!ft_strcmp(graph[i]->name, graph[info->count_node]->name))
			error("A vertex with this name already exists\n", graph, info);
		i++;
	}
	info->count_node++;
}

void	get_rooms_links(t_graph **graph, t_info *info)
{
	int flag;
	char *line;
	char *name;
	int i;
	int j;

	flag = 0;
	i = 0;
	while (get_next_line(0, &line, 0) > 0)
	{
		if (*line == '#')
		{
			if (!ft_strcpy("##start\n", line))
			{
				free(line);
				get_next_line(0, &line, 0);
				get_room(graph, info, flag, line);
				info->ind_start = info->count_node;
			}
			else if (!ft_strcpy("##end\n", line))
			{
				free(line);
				get_next_line(0, &line, 0);
				get_room(graph, info, flag, line);
				info->ind_end = info->count_node;
			}
		}
		else if (ft_strchr((const char*)(line), ' ') != NULL)
			get_room(graph, info, flag, line);
		else if (ft_strchr((const char*)(line), '-') != NULL)
		{
			flag = 1;
			name = ft_strsub((const char *)(line), 0, ft_strrchr((const char*)(line), '-') - line);
			i = 0;
			while (i < info->count_node)
			{
				if (!ft_strcmp(name, graph[i]->name))
					break ;
				i++;
			}
			if (i == info->count_node)
				error("Such a room does not exist in the graph. Unable to create path\n", graph, info);
			free(name);
			if (graph[i]->link == NULL)
				graph[i]->link = new_links(*graph, info);
			name = ft_strsub((const char *)(line), (unsigned int)(ft_strrchr((const char*)(line), '-') + 1), ft_strlen(line));
			j = 0;
			while (j < info->count_node)
			{
				if (!ft_strcmp(name, graph[j]->name))
					break ;
				j++;
			}
			if (j == info->count_node)
				error("Such a room does not exist in the graph. Unable to create path\n", graph, info);
			free(name);
			if (graph[j]->link == NULL)
				graph[j]->link = new_links(*graph, info);
			graph[i]->link[j / sizeof(size_t) * 8] = 1 << (j % sizeof(size_t) * 8);
			graph[j]->link[i / sizeof(size_t) * 8] = 1 << (j % sizeof(size_t) * 8);
		}
		else
			error("Incorrect input\n", graph, info);
		free(line);
	}
}