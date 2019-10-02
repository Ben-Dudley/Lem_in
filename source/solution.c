/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:11:16 by hharrold          #+#    #+#             */
/*   Updated: 2019/09/20 20:50:10 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Solution determine which option this better,
** find stack max flow path and shortest path stack.
** It choose best variant and move ants.
** Here also is search paths max flow stack.
*/

int					score_stack_path(t_graph **graph, t_info *info,
										int *queue, int *traces)
{
	int				count;
	int				add_path;

	count = 0;
	add_path = find_path(graph, info, queue, traces);
	while (add_path > 0)
	{
		count += add_path;
		add_path = find_path(graph, info, queue, traces);
	//	printf("\nin score_stack_path add_path %d count %d\n", add_path, count);
	}
	clear_graph(graph, info);
	return (count);
}

int					find_link_node(t_graph **graph, t_info *info, int node)
{
	t_link			*temp;

	temp = graph[0][info->ind_end].link;
	while (temp)
	{
		if (temp->node == node)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void				get_path_numbers(t_graph **graph, t_info *info)
{
	t_link			*temp;
	t_path			*path;
	int				i;

	i = 0;
	while (++i <= info->max_flow)
	{
		temp = graph[0][info->ind_start].link;
		path = new_path(graph, info);
		add_path(&info->path, path);
		add_node(&path->node, new_node(graph, info, info->ind_start));
		in_stack_add(graph, info, info->path->stack, path); // stack
		path->stack = info->max_flow;
	//	printf("save_path  %d - (%s)\n", path->node->node, graph[0][path->node->node].name);
		while (temp && temp->node != info->ind_end)
		{
	//		printf("save*path  %d - (%s)\n", path->node->node, graph[0][path->node->node].name);
	//		printf("graph[0][temp->node].visited %d - %d\n", graph[0][temp->node].visited , i);
			if (graph[0][temp->node].visited == i) // i  || temp->node == info->ind_start
			{
				add_node(&path->node, new_node(graph, info, temp->node));
	//			printf("save+path  %d - (%s)\n", path->node->node, graph[0][path->node->node].name);
				++info->path->length;
				temp = graph[0][temp->node].link;
			}
			else
				temp = temp->next;
		}
		add_node(&path->node, new_node(graph, info, info->ind_end));
	}
	//printf("!!!!!!!\n");
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
	if (temp && temp->stack == info->max_flow)
		printf(" \n ");
}
void			for_fix_stack(t_graph **graph, t_info *info)
{
	t_stack		*st;
	t_path		*temp;
	t_node		*nodo4ka;

	st = info->stack;
	while (st)
	{
		printf("\nStack#%d ", st->stack);
		temp = st->path;
		while (temp)
		{
			printf("len path %d, ", temp->length);
			nodo4ka = temp->node;
			while (nodo4ka)
			{
				printf(" %d - (%s) ", nodo4ka->node, graph[0][nodo4ka->node].name);
				nodo4ka = nodo4ka->next;
			}
			temp = temp->next;
		}
		st = st->next;
		printf("\n");
	}
	printf("\n");
}
//void			sort_algorithm(t_graph	**graph, int i);
//{
//	t_link	*link;
//
//	link = graph[0][i].link;
//	while(link)
//	{
//		graph[0][link->node].weight
//	}
//}
//
//void			sort_link_for_weight(t_graph **graph, t_info *info)
//{
//	int 	i;
//
//	i = 0;
//	while(i < info->count_node)
//	{
//		sort_algorithm(graph, i);
//		i += 1;
//	}
//}

void			print_stack(t_graph **graph, t_info *info)
{
	t_stack		*st;
	t_path		*temp;
	t_node		*nodo4ka;

	st = info->stack;
	while (st)
	{
		temp = st->path;
		while (temp)
		{
			nodo4ka =  temp->node;
			printf("длина пути %d, стек № %d \n", temp->length, temp->stack);
			while (nodo4ka)
			{
				printf(" %d - (%s) ", nodo4ka->node, graph[0][nodo4ka->node].name);
				nodo4ka = nodo4ka->next;
			}
			printf(" \n ");
			temp = temp->next;
		}
		if (temp && temp->stack == info->max_flow)
			printf(" \n ");
		st = st->next;
	}
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
	printf("\n");
}

int					stack_max_flow(t_graph **graph, t_info *info,
						int index, int flow, int length)
{
	t_link			*temp;

	if (flow > info->max_flow)
		return (1);
	temp = graph[0][index].link;
//	printf("MAX_FLOW %d\n", flow);
	if (flow == 12) // delete>???!!?!?!?!?!
	{
		printf("SEX!\n");
		return (0);
	}
	while (temp)
	{
		//print_massiv(graph, info);
		if (graph[0][temp->node].visited == 0 && temp->node != info->ind_start)
		//	&& temp->status == 1)
		{
			//printf("temp->node %d \n", temp->node);
		//	printf("name(%s) v-%d\n", graph[0][temp->node].name, flow);
			graph[0][temp->node].visited = flow;
			temp->status = 0;
			temp->reverse->status = 0;
		//	temp->status
//			printf("3stack_max_flow\n");
			if (find_link_node(graph, info, temp->node))
			{
		//		printf("!!!!!!!!!!!stack_max_flow\n");
		//	printf("length way #%d - %d\n", flow, length);
			if (flow > 1)
				return (0);
				if (stack_max_flow(graph, info, info->ind_start, flow + 1, 0))
					return (1);
		//		printf("DELETE****name(%s) v-%d\n", graph[0][temp->node].name, graph[0][temp->node].visited);
				//graph[0][temp->node].visited = 0;
				temp->status = 1;
				return (0);
			}
		//	printf("4stack_max_flow\n");
			if (stack_max_flow(graph, info, temp->node, flow, length + 1))
				return (1);
		//	printf("DELETE!!!name(%s) v-%d\n", graph[0][temp->node].name, graph[0][temp->node].visited);
			//graph[0][temp->node].visited = 0;
			temp->status = 1;
		}
		temp = temp->next;
		//printf("5stack_max_flow\n");
	}
	return (0);
}


//int         f(t_graph **graph, t_info *info, int node, int last_node)
//{
//	t_link *temp;
//	int result;// все строчки помеенные **** для последнего ретерна - понял именно так
//	result = 0; //****
//	if (node == info->ind_end) // если захожу в энд
//	{ //то из енд к этой вершине
//		printf("12332345654323456654323454345543456765434566543456543å\n");
//		graph[0][last_node].link->status = 0; // я ставлю t->status = 0
//		return(1); // и выхожу из рекурсии
//	}
//	temp = graph[0][node].link;
//	while(temp) // иду по ребрам
//	{
//		printf("1\n");
//		if (temp->node == info->ind_end) //пока не найду енд
//		{
//			printf("2\n");
//			// если захожу в энд
//			//то из енд к этой вершине
//			graph[0][last_node].link->status = 0; // я ставлю t->status = 0
//			printf("12332345654323456654323454345543456765434566543456543å\n");
//			return(1); // и выхожу из рекурсии
//		}
//		printf("9\n");
//		temp->status = 0; // и ставлю 0 t->status
//		graph[0][temp->node].visited = 1; // и визитед 1
//		result = f(graph, info, temp->node, node); // ****
//		if (result == 1 && temp->status == 0 && temp->reverse->status == 0) // если // ****
//		{// из рекурсии вернулась единица и t->status = 0 and t_reverse->status=0 // т реверс где??????
//			printf("3\n");
//			graph[0][temp->node].weight = 1;//поставь weight // на единицу?
//			//дальше верни линки // всмысле return()?? но там int
//			graph[0][temp->node].visited = 1;// и поставь visible 1 // не visited??
//			return(1);
//		}
//		else if(result == 0 && graph[0][temp->node].weight == 0) // **** //return (пока у вершин нет веса) // или вес -1??
//		{
//			printf("4\n");
//			temp->status = 1; //создать там status 1 visible 1
//			graph[0][temp->node].visited = 1;
//		}
//		else // tyt hz
//			temp = temp->next;
//		//return(0);
//		temp = temp->next;
//	}
//	printf("5\n");
//	graph[0][temp->node].weight = -1; //если я прошла по всем link и не нашла end поставить weight = -1
//	return (0); // (пока у вершин нет веса) // то есть возврашаю 0 пока вес -1? или 0? // для этого сделал переменную i и пометил все строчки ****
//}// не понял последние две строчки
// int				f(t_graph **graph, t_info *info, int node, int last_node)
//{
//	t_link		*temp;
//	int 		result;
//
//	if (node == info->ind_end)
//	{
//
//	}
//	result = 0;
//	temp = graph[0][node].link;
//
//	while (temp)
//	{
//		if (graph[0][temp->node].visited == 1) // && graph[0][temp->node].weight == 1
//			result = f(graph, info, temp->node, node);
//		if (temp->node == info->ind_end)
//		{
//
//		}
//		temp = temp->next;
//	}
//	return (0);
//}



//int				priority(t_graph **graph, t_info *info, int index, int length)
//{
//	t_link			*temp;
//
//	temp = graph[0][index].link;
//	while (temp)
//	{å
//		if (temp->node == info->ind_end)
//			return (1);
//		if (graph[0][index].weight < graph[0][temp->node].weight)
//		{
//			graph[0][index].weight = length;
//			if (priority(graph, info, temp->node, length + 1))
//			{
//
//				return ()
//			}
//
//		}
//		temp = temp->next;
//	}
//	return (0);
//}
//
//int				ft_priority(t_graph **graph, t_info *info, int index, int length)
//{
//	t_link			*temp;
//	int 			res;
//
//	res = 0;
//
//	temp = graph[0][index].link;
//	while (temp)
//	{
//		if (temp->node == info->ind_end)
//			return (length);
//		if (graph[0][index].weight < graph[0][temp->node].weight)
//		{
//			graph[0][index].weight = length;
//			res = priority(graph, info, temp->node, length + 1));
//			if (res < length)
//			{
//				graph[0][index].weight = 2147483647; // или -1 или (length -1)
//				return (length - 1);
//			}
////			else
//				//graph[0][index].weight = res - 1;
//		}
//		temp = temp->next;
//	}
//	return (length);
//}



int					solution(t_graph **graph, t_info *info)
{
	int				*queue;
	int				*traces;
	int				stack;

	if (!(queue = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error_message(graph, info, 0);
	if (!(traces = (int *)malloc(sizeof(int) * (info->count_node + 1))))
		error_message(graph, info, 0);
//	ft_print_pyti(graph, info);
//	printf("dasdfsaad\n");
//	f(graph, info,info->ind_start, 0);
	//clear_graph(graph, info);
//	priority(graph, info, info->ind_start, 0);
	stack = score_stack_path(graph, info, queue, traces); // count min flow and path min flow
 	info->count_ants *= -1;
	info->max_flow = score_stack_path(graph, info, queue, traces); //count max flow
	info->count_ants *= -1;
//	printf("in solution count ants %d\n", info->count_ants);
	//print_stack(graph, info);
	if (info->max_flow <= 0)
		error_message(graph, info, 1);
	if (stack < info->max_flow)
	{
	//	printf("1solution\n");
	//	ft_print_pyti(graph, info);
	//	printf("6solution\n");
		stack_max_flow(graph, info, info->ind_start, 1, 0); //path max flow
//		printf("2solution\n");
		get_path_numbers(graph, info);
		//print_stack(graph, info);
//	printf("3solution\n");
		clear_graph(graph, info);
//		printf("4solution\n");
		stack = score_ants(graph, info, stack);
//	printf("5solution\n");
	}
	for_fix_stack(graph, info);
	Merge_Sort(graph, info);
	for_fix_stack(graph, info);
//	sleep(1000);
	free(queue);
	free(traces);
	ft_print_pyti(graph, info);
	score_ways(graph, info, stack);

//	printf("7solution\n");
	return (1);
}
