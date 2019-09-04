/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:29:59 by bdudley           #+#    #+#             */
/*   Updated: 2019/08/30 18:15:43 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(char *str, t_graph **graph, t_info *info)
{
	int i;

	i = 0;
//	while (i < info->count_node)
//		if (graph[0][i].link)
//			free_link(&graph[0][i++].link);
//	free(graph[0]);
	ft_putstr_fd(str, 2);
	exit(3);
}

void	init(t_graph **graph, t_info *info)
{
	*graph = NULL;
	info->count_ants = 0;
	info->count_node = 0;
	info->max_flow = 0;
	info->count_max_node = SIZE;
	info->ind_start = -1;
	info->ind_end = -1;
}

int		main(void)
{
	t_graph *graph;
	t_info	info;

	init(&graph, &info);
	get_ants(&graph, &info);
	get_rooms_links(&graph, &info);

	if (!solution(&graph, &info))
		ft_putstr("GGWP\n");
	error("", &graph, &info);
	return (0);
}
