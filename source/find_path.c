
#include "lem_in.h"

static int			init_mass(t_info *info, int *queue, int *traces)
{
	int			i;

	i = 1;
	queue[0] = info->ind_start;
	while (i <= info->count_node)
		queue[i++] = -1;
	i = 0;
	while (i <= info->count_node)
		traces[i++] = -1;
	return (-1);
}

static int			find_index(t_info *info, int *queue, int node)
{
	int		j;

	j = 0;
	while (j <= info->count_node)
	{
		if (queue[j] == node)
			break ;
		j++;
	}
	return (j);
}

static int			get_path(t_graph **graph, t_info *info, int *traces,
							   int flag)
{
	if (flag)
		save_path(graph, info, traces);
	else
		restoration_path(graph, info, traces);
	return (1);
}

int					find_path(t_graph **graph, t_info *info,
								 int *queue, int *traces)
{
	int			i;
	int			j;
	t_link		*ptr;

	i = init_mass(info, queue, traces);
	j = 0;
	while (queue[++i] != -1)
	{
		ptr = graph[0][queue[i]].link;
		while (ptr)
		{
			if (ptr->status != 0 && graph[0][ptr->node].visited == 0)
				if (find_index(info, queue, ptr->node) == info->count_node + 1)
				{
					queue[++j] = ptr->node;
					traces[ptr->node] = queue[i];
					if (ptr->node == info->ind_end)
						return (get_path(graph, info, traces,
								(info->count_ants > 0) ? 1 : 0));
				}
			ptr = ptr->next;
		}
	}
	return (0);
}
