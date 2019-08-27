/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms_ants.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:21:20 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/27 15:21:26 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			get_ants(t_graph **graph, t_info *info)
{
	char *line;

	while (get_next_line(0, &line) > 0)
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

static void		ft_help_get_room(t_graph **graph, t_info *info, int flag,
																	char *line)
{
	char		*name;
	char		*name_copy;

	name = ft_strsub((const char *)(line),
	(unsigned int)(ft_strrchr((const char*)(line), ' ') + 1 - line),
	line + ft_strlen(line) - ft_strrchr((const char*)(line), ' ') - 1);
	graph[0][info->count_node].y = put_number(name, graph, info);
	free(name);
	name = ft_strsub((const char *)(line), 0,
	ft_strrchr((const char*)(line), ' ') - line);
	name_copy = ft_strsub((const char *)(name),
	(unsigned int)(ft_strrchr((const char*)(name), ' ') + 1 - name),
	name + ft_strlen(name) - ft_strrchr((const char*)(name), ' ') - 1);
	graph[0][info->count_node].x = put_number(name_copy, graph, info);
	free(name_copy);
	name_copy = ft_strsub((const char *)(name), 0,
	ft_strrchr((const char*)(name), ' ') - name);
	graph[0][info->count_node].name = name_copy;
	free(name);
}

void			get_room(t_graph **graph, t_info *info, int flag, char *line)
{
	t_graph		*node;
	int			i;

	i = 0;
	if (flag == 1)
		error("First you need to enter all the vertices, and only then links\n",
																graph, info);
	if (*line == 'L')
		error("The vertex name cannot start with character 'L'\n",
																graph, info);
	if (info->count_node >= info->count_max_node || info->count_node == 0)
		graph[0] = new_graph(graph[0], info);
	ft_help_get_room(graph, info, flag, line);
	while (i < info->count_node)
	{
		if (!ft_strcmp(graph[0][i].name, graph[0][info->count_node].name))
			error("A vertex with this name already exists\n", graph, info);
		++i;
	}
	info->count_node++;
}
