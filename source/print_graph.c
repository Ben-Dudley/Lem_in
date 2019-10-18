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

static void			add_str_in_buf(t_info *info, char *str)
{
	print_buf(info, str);
	print_buf(info, "\n");
	free(str);
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
	print_buf(info, info->basic_information);
	if (info->flag_score_in_file == 0)
	{
		free(info->basic_information);
	}
	print_buf(info, "\n");
}
