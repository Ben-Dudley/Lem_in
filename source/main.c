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
			buf_init(info);
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
	info->flag_score_in_file = 0;
	info->flag_way = 0;
	info->flag_all_way = 0;
	info->flag_print_graph = 0;
	info->buf_size = 100;
	info->stack = NULL;
	(info->basic_information) = ((char*)malloc(sizeof(char) * info->buf_size));
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
	info.len_buf = 0;
	check(&graph, &info);
	if (!solution(&graph, &info))
		ft_putstr("GGWP\n");
	buf_init(&info);
	print_flags(&info);
	if (info.flag_print_graph == 1)
		print_flag_graph(&graph, &info);
	error_message(&graph, &info, -1);
	return (0);
}
