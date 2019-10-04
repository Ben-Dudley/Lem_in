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

void				print_move(t_graph **graph, t_info *info, int count,
															int count_ways)
{
	t_path		*temp;
	t_node		*temp_node;
	int			i;
	int			counter;

	i = min_score_ants(info, count, count_ways);
//	printf("TUTU!!!!!!!\n");
	while (i < count)
	{
		counter = i;
		temp = info->stack->path;
		while (temp)
		{
			temp_node = temp->node;
			while (temp_node)
			{
				i += send_to_print_steps(temp_node, i, info, graph);
				temp_node = temp_node->next;
			}
			temp = temp->next;
		}
		if (counter == i)
			i++;
	}
	print_buf(info, "\n");
	if (info->flag_score > 0)
		info->flag_score += 1;
	info->count_max_node *= -1;
}

void				print_node(int i, t_info *info, t_graph **graph)
{
	char *str;

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
	print_buf(info, str);
	free(str);
	print_buf(info, "\n");
}

void				print_link(char *name_node_1, char *name_node_2,
										t_info *info, t_graph **graph)
{
	print_buf(info, name_node_1);
	print_buf(info, "-");
	print_buf(info, name_node_2);
	print_buf(info, "\n");
}

void				print_graph(t_graph **graph, t_info *info)
{
	int		i;
	t_link	*temp;
	char	*str;

	i = -1;
	if (!(str = ft_itoa(info->count_ants)))
		error_message(graph, info, 0);
	print_buf(info, str);
	print_buf(info, "\n");
	free(str);
	while (++i < info->count_node)
		print_node(i, info, graph);
	i = -1;
	while (++i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			if (temp->status != -1)
			print_link(graph[0][i].name,
					graph[0][temp->node].name, info, graph);
			temp->status = -1;
			temp->reverse->status = -1;
			temp = temp->next;
		}
	}
	print_buf(info, "\n");
}
