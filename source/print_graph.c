/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 17:24:18 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/19 21:27:54 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					send_to_print_steps(t_node *temp_node, int i,
									t_info *info, t_graph **graph)
{
	char	*str;

	if (i == temp_node->ant)
	{
		if (temp_node->ant)
		{
			if (!(str = ft_itoa(temp_node->ant)))
				error_message(graph, info, 0);
			if (info->count_max_node < 0)
				print_buf(info, " ");
			else
				info->count_max_node *= -1;
			if (info->flag_colour && temp_node->node == info->ind_end)
				print_buf(info, "\033[1;35m");
			print_buf(info, "L");
			print_buf(info, str);
			free(str);
			print_buf(info, "-");
			print_buf(info, graph[0][temp_node->node].name);
			if (info->flag_colour && temp_node->node == info->ind_end)
				print_buf(info, "\033[0m");
		}
		return (1);
	}
	return (0);
}

static void			print_link(char *name_node_1, char *name_node_2,
								t_info *info, t_graph **graph)
{
	print_buf(info, name_node_1);
	print_buf(info, "-");
	print_buf(info, name_node_2);
	print_buf(info, "\n");
}

static void			add_str_in_buf(t_info *info, char *str)
{
	print_buf(info, str);
	print_buf(info, "\n");
	free(str); // если тут фришить str, то норм???
}

void				print_node(int i, t_info *info, t_graph **graph)
{
	char		*str;

	if (i == info->ind_start)
		print_buf(info, "##start\n");
	if (i == info->ind_end)
		print_buf(info, "##end\n");
	print_buf(info, graph[0][i].name);
	print_buf(info, " ");
	if (!(str = ft_itoa(graph[0][i].x)))
		error_message(graph, info, 0);
	print_buf(info, str);
	print_buf(info, " ");
	free(str);
	if (!(str = ft_itoa(graph[0][i].y)))
		error_message(graph, info, 0);
	add_str_in_buf(info, str);
}

void				print_graph(t_graph **gr, t_info *info)
{
	int		i;
	t_link	*temp;
	char	*str;

	i = -1;
	if (!(str = ft_itoa(info->count_ants)))
		error_message(gr, info, 0);
	add_str_in_buf(info, str);
	while (++i < info->count_node)
		print_node(i, info, gr);
	i = -1;
	while (++i < info->count_node)
	{
		temp = gr[0][i].link;
		while (temp)
		{
			if (temp->status != -1)
				print_link(gr[0][i].name, gr[0][temp->node].name, info, gr);
			temp->status = -1;
			temp->reverse->status = -1;
			temp = temp->next;
		}
	}
	print_buf(info, "\n");
}
