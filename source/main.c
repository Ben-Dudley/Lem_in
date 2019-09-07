/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:29:59 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/07 19:47:44 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			check(t_graph **graph, t_info *info)
{
	if (!*graph)
		error_message(graph, info, 2);
	else if (!graph[0][0].link)
		error_message(graph, info, 2);
}

void			init(t_graph **graph, t_info *info)
{
	*graph = NULL;
	info->count_ants = 0;
	info->count_node = 0;
	info->max_flow = 0;
	info->count_max_node = SIZE;
	info->ind_start = -1;
	info->ind_end = -1;
	info->len_buf = 0;
	ft_bzero(info->buf, BUFF);
}

int				main(void)
{
	t_graph *graph;
	t_info	info;

	init(&graph, &info);
	if (!get_ants(&graph, &info))
		error_message(&graph, &info, 4);
	get_rooms_links(&graph, &info);
//	printf("cvcv\n");
	check(&graph, &info);
	if (!solution(&graph, &info))
		ft_putstr("GGWP\n");
	buf_init(&info);
	error_message(&graph, &info, -1); // просто фришит
	return (0);
}
