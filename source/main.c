/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:29:59 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/19 21:25:41 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			buf_init(t_info *info)
{
	write(1, info->buf, info->len_buf);
	ft_bzero(info->buf, BUFF);
	info->len_buf = 0;
}

void			print_buf(t_info *info, char *str)
{
	while (*str != '\0')
	{
		info->buf[info->len_buf++] = *str;
		++str;
		if (info->len_buf == BUFF)
		{
			write(1, info->buf, info->len_buf);
			ft_bzero(info->buf, BUFF);
			info->len_buf = 0;
			buf_init(info);
		}
	}
}

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
	info->flag_visual = 0;
	info->flag_colour = 0;
	info->flag_score = 0;
	info->flag_way = 0;
	info->flag_all_way = 0;
	info->flag_print_graph = 0;
	ft_bzero(info->buf, BUFF);
}

int				main(int ac, char **av)
{
	t_graph *graph;
	t_info	info;

	init(&graph, &info);
	if (ac > 1)
		flag_checking(ac, av, &graph, &info);
	if (!get_ants(&graph, &info))
		error_message(&graph, &info, 4);
	get_rooms_links(&graph, &info);
	check(&graph, &info);
//	printf("info->count_ants in main %d\n", info.count_ants);
	if (!solution(&graph, &info))
		ft_putstr("GGWP\n");
	buf_init(&info);
	error_message(&graph, &info, -1);
	return (0);
}
