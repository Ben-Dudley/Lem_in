/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 17:24:18 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/07 20:15:01 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 				min_score_ants(t_graph **graph, t_info *info)
{

	//ft_print_pyti(graph, info);
	return (0);
}

void		buf_init(t_info *info)
{
	//printf("\nstroka govna tyta i tato4ki\n");
	write(1, info->buf, BUFF);
	ft_bzero(info->buf, BUFF);
	info->len_buf = 0;
}

void 		print_buf(t_info *info, char *str)
{
	//printf("\nstroka govna tyta  - |%s|\n", str);
	while (*str != '\0')
	{
		info->buf[info->len_buf++] = *str;
		++str;
		if (info->len_buf == BUFF)
			buf_init(info);
	}
}

void		print_steps(int ant, char *name,  t_info *info, t_graph **graph)
{
	int 	j;
	char 	*str;

	j = 0;
	print_buf(info, "L");

	if (!(str = ft_itoa(ant)))
		error_message(graph, info, 0);
	print_buf(info, str);
	free(str);
	print_buf(info, "-");
//	printf("|%s|\n", name);
	print_buf(info, name);
	//короче последний пробел в строке
	//if (1)
		print_buf(info, " ");

}

void				print_move(t_graph **graph, t_info *info, int count)
{
	t_path		*temp;
	t_node		*temp_node;
	int			i;
	int			counter;

	i = min_score_ants(graph, info);
	while (i < count)
	{
		counter = i;
		temp = info->path;
		while (temp)
		{
			temp_node = temp->node;
			while (temp_node)
			{
				if (i == temp_node->ant)
				{
					if (temp_node->ant)
						print_steps(temp_node->ant, graph[0][temp_node->node].name, info, graph);
							//printf("L%d-%s ", temp_node->ant, graph[0][temp_node->node].name); //space
					++i;
				}
				temp_node = temp_node->next;
			}
			temp = temp->next;
		}
		if (counter == i)
			i++;
	}
//	printf("\n");
	print_buf(info, "\n");
}

void				steps_ants(t_graph **graph, t_info *info, int *ways, int count_ways)
{
	t_node		*ptr_node;
	t_path		*ptr_path;
	int			j;
	int			i;
	int			score_ants;

	j = 1;
	score_ants = 0;
	print_graph(graph, info);
	while (score_ants < info->count_ants)
	{
		i = 0;
		ptr_path = info->path;
		while (ptr_path)
		{
			ptr_node = ptr_path->node;
			if (ptr_node->node && !ptr_node->next->node)
				score_ants += 1;
			while (ptr_node->next->node != info->ind_start)
			{
				ptr_node->ant = ptr_node->next->ant;
				if (ptr_node->node == info->ind_end && ptr_node->next->ant != 0)
					score_ants += 1;
				ptr_node = ptr_node->next;
			}
			if (ways[i] > 0)
			{
				ptr_node->ant = j;
				j++;
				ways[i] -= 1;
			}
			else
				ptr_node->ant = 0;
			++i;
			ptr_path = ptr_path->next;
		}
		print_move(graph, info, j);
	}
}
void		print_node(int i, t_info *info, t_graph **graph)
{
	char *str;
	if (i != -1)
	{
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
	}
	else
	{
		if (!(str = ft_itoa(info->count_ants)))
			error_message(graph, info, 0);
		print_buf(info, str);
	}
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
	int			i;
	t_link		*temp;

	i = 0;
	//printf("%d\n", info->count_ants);
	print_node(-1, info, graph);
	while (i < info->count_node)
	{
		print_node(i, info, graph);
		//printf("%s %d %d\n", graph[0][i].name, graph[0][i].x, graph[0][i].y);
		i++;
	}
	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp && temp->status != 0)
		{
			print_link(graph[0][i].name, graph[0][temp->node].name, info, graph);
			//printf("%s-%s\n", graph[0][i].name, graph[0][temp->node].name); //two print link
			temp->status = 0;
			temp->reverse->status = 0;
			temp = temp->next;
		}
		++i;
	}
	print_buf(info, "\n");
	//printf("\n");
}
