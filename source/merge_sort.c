//
// Created by Henly Harrold hardyng on 02/10/2019.
//

//struct node
//{
//	int number;
//	struct node *next;
//};

//struct node *addnode(int number, struct node *next)
//{
//	struct node *tnode;
//	tnode = (struct node*)malloc(sizeof(*tnode));
//	if(tnode != NULL)
//	{
//		tnode->number = number;
//		tnode->next = next;
//	}
//	return tnode;
//}
#include "lem_in.h"

int Length(t_link *head)
{
	int		count;
	t_link	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count += 1;
		current = current->next;
	}
	return(count);
}



t_link *SortedMerge(t_graph **graph, t_link *a, t_link *b)
{
	t_link *result;

	result = NULL;
	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);
	if (graph[0][a->node].weight <= graph[0][b->node].weight)
	{
		result = a;
		result->next = SortedMerge(graph, a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(graph, a, b->next);
	}
	return(result);
}


//void Merge_Sort(struct node** headRef)
//{
//	struct node* head = *headRef;
//	struct node* a;
//	struct node* b;
//	// вырожденный случай – длина списка равно 0 или 1
//	if ((head == NULL) || (head->next == NULL))
//	{
//		return;
//	}
//	FrontBackSplit(head, &a, &b);
//	Merge_Sort(&a); // рекурсивная сортировка подсписков
//	Merge_Sort(&b);
//	*headRef  = SortedMerge(a, b);
//}

void FrontBackSplit(t_link *source,
					t_link **frontRef,
					t_link **backRef)
{

	int len;
	int i;
	t_link *current;
	int hopCount;

	current = source;
	len = Length(source); // заменить
	i = 0;
	if (len < 2)
	{
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		hopCount = (len-1)/2;
		while(i < hopCount)
		{
			current = current->next;
			i += 1;
		}
		// исходный список разбивается на два подсписка
		*frontRef = source;
		*backRef = current->next;
		current->next = NULL;
	}
}

void 	MergeSort(t_graph **graph, t_link **base)
{
	t_link	*link;
	t_link	*a;
	t_link	*b;
	link = *base;
	if ((link == NULL) || (link->next == NULL))
		return;
	FrontBackSplit(link, &a, &b);
	MergeSort(graph, &a); // рекурсивная сортировка подсписков
	MergeSort(graph, &b);
	*base = SortedMerge(graph, a, b);
}

void	Merge_Sort(t_graph **graph, t_info *info)
{
	int 	i;

	i = 0;
	while(i < info->count_node)
	{
		MergeSort(graph, &graph[0][i].link);
		i += 1;
	}
}