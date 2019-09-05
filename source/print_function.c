/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:30:15 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/02 15:30:18 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print(t_graph **graph, t_info *info)
{
	int			i;
	t_link		*temp;

	i = 0;
	ft_putnbr(info->count_ants); /*колличество муравьев*/
	while (i < info->count_node)
	{
		ft_putstr(graph[0][i].name);
		ft_putchar(' ');
		ft_putnbr(graph[0][i].x);
		ft_putchar(' ');
		ft_putnbr(graph[0][i].y);
		ft_putchar('\n');
		i++;
	}
	i = 0;
	while (i < info->count_node)
	{
		temp = graph[0][i].link;
		while (temp)
		{
			ft_putstr(graph[0][i].name);
			ft_putchar('-');
			ft_putstr(graph[0][temp->node].name);
			ft_putchar('\n');
			temp = temp->next; // убрать двойной вывод или как то так
		}
		++i;
	}
	ft_putchar('\n'); // нафига
}

void		print_ant_in_room(int ant, char *name_room)// и данные
{//о последнем муравье чтобы не ставить пробел
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(name_room);
	if (1) // вот сюда данные запихать
		ft_putchar(' ');
	//ft_putchar('\n');
}


void			print_massiv(t_graph **graph, t_info *info)
{
	int			i;
	t_link		*temp;

	i = 0;
	while (i < info->count_node)
	{
		printf(" %d(%s) ", graph[0][i].visited, graph[0][i].name);// удалить заменить
		i++;
	}
	i = 0;
	printf("\n");
}


void			print_ways(t_info *info, int *ways, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		printf(" %d ", ways[i]);
		++i;
	}
	printf("\n");
}

void			ft_print_pyti(t_graph **graph, t_info *info)
{
	t_path		*temp;
	t_node		*nodo4ka;
	temp = info->path;
	while (temp)
	{
		nodo4ka =  temp->node;
		printf("\nlen - %d, stack - %d \n", temp->length, temp->stack);
		while (nodo4ka)
		{
			printf(" %d - (%s) ", nodo4ka->node, graph[0][nodo4ka->node].name);
			nodo4ka = nodo4ka->next;
		}
		printf(" \n ");
		temp = temp->next;
	}
	printf(" \n ");
}

void			reverse_path(t_graph **graph, t_info *info)
{
	t_path *temp;

	temp = info->path;
	while (temp)
	{
		reverse_node(&temp);
		temp = temp->next;
	}
}
