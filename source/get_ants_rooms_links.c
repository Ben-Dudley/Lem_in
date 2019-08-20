/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants_rooms_links.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:52:17 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/20 21:43:59 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			put_number(char *str, t_graph **graph, t_info **info)
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
		error(a, NULL, NULL);
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

void	get_ants(t_graph **graph, t_info **info)
{
	char *line;

	while (get_next_line(0, &line, 0) > 0)
	{
		if (*line == '#' && *(line + 1) != '#')
			continue ;
		else if (ft_isdigit(*line))
		{
			(*info)->count_ants = put_number(line);
			free(line);
			if ((*info)->count_ants < 0)
				error("The number of ants can only be positive\n", graph, info);
			return ;
		}
		else
			error("First you need to enter the number of ants\n", graph, info);
		free(line);
	}
}

t_graph		*get_room(t_graph **graph, t_info **info, int flag, char *line)
{
	char *name;
	char *name_copy;
	t_graph *node;
	t_graph *graph_copy;

	if (flag == 1)
		error("First you need to enter all the vertices, and only then links\n", graph, info);
	if (*line == 'L' || *line == '#')
		error("The vertex name cannot start with characters '#' and 'L'\n", graph, info);
	node = new_graph(NULL, NULL);
	name = ft_strsub((const char *)(*line), ft_strrchr((const char*)(*line), ' '), ft_strlen(*line));
	node->y = put_number(name, graph, info);
	free(name);
	name = ft_strsub((const char *)(*line), 0, ft_strrchr((const char*)(*line), ' '));
	name_copy = ft_strsub((const char *)(*name), ft_strrchr((const char*)(*name), ' '), ft_strlen(*name));
	free(name_copy);
	node->x = put_number(name_copy, graph, info);
	name_copy = ft_strsub((const char *)(*name), 0,  ft_strrchr((const char*)(*name), ' '));
	node->name = name_copy;
	free(name);
	graph_copy = *graph;
	while (graph_copy)
	{
		if (!ft_strcmp(graph_copy->name, node))
		{
			free_graph(&node);
			error("A vertex with this name already exists\n", graph, info);
		}
		graph_copy = graph_copy->next;
	}
	return (node);
}

void	get_rooms_links(t_graph **graph, t_info **info)
{
	int flag;
	char *line;
	char *name;

	flag = 0;
	while (get_next_line(0, &line, 0) > 0)
	{
		if (*line == '#' && *(line + 1) == '#')
		{
			if (!ft_strcpy("##start\n", line))
			{
				free(line);
				get_next_line(0, &line, 0);
				get_room(graph, info, flag, line);
			}
			else if (!ft_strcpy("##end\n", line))
			{
				free(line);
				get_next_line(0, &line, 0);
				get_room(graph, info, flag, line);
			}
		}
		else if (ft_strchr((const char*)(*line), ' ') != NULL)
			get_room(graph, info, flag, line);
		else if (ft_strchr((const char*)(*line), '-') != NULL)
		{
			flag = 1;
			name = ft_strsub((const char *)(*line), 0, ft_strrchr((const char*)(*line), '-'));

			name = ft_strsub((const char *)(*line), ft_strrchr((const char*)(*line), '-'), ft_strlen(*line));
		}
		free(line);
	}
}