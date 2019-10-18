/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:21:56 by hharrold          #+#    #+#             */
/*   Updated: 2019/10/17 18:22:00 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			send_stack_to_print(int stack, t_info *info)
{
	char	*str;

	str = ft_itoa(stack);
	print_buf(info, "\033[0;32m");
	print_buf(info, "\nStack#");
	print_buf(info, str);
	print_buf(info, "\033[0m");
	print_buf(info, " \n");
	free(str);
}

static void			send_path_to_print(int path, t_info *info)
{
	char	*str;

	str = ft_itoa(path);
	print_buf(info, "\033[0;34m");
	print_buf(info, "len path ");
	print_buf(info, str);
	print_buf(info, ": \033[0m");
	free(str);
}

static void			send_node_to_print(int node, char *name, t_info *info)
{
	char	*str;

	str = ft_itoa(node);
	print_buf(info, str);
	print_buf(info, "\033[0;33m");
	print_buf(info, " - (");
	print_buf(info, name);
	print_buf(info, "); ");
	print_buf(info, "\033[0m");
	free(str);
}

void				for_flag_v(t_graph **graph, t_info *info)
{
	t_stack		*st;
	t_path		*temp;
	t_node		*n;

	st = info->stack;
	while (st)
	{
		send_stack_to_print(st->stack, info);
		temp = st->path;
		while (temp)
		{
			send_path_to_print(temp->length, info);
			n = temp->node;
			while (n)
			{
				send_node_to_print(n->node, graph[0][n->node].name, info);
				n = n->next;
			}
			temp = temp->next;
			print_buf(info, "\n");
		}
		st = st->next;
	}
	print_buf(info, "\n");
	buf_init(info);
}
