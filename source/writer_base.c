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

static void				ft_remalloc(t_info *info)
{
	char		*temp;
	int			i;

	temp = info->basic_information;
	info->buf_size *= 2;
	(info->basic_information) = ((char*)malloc(sizeof(char) * info->buf_size));
	i = 0;
	while (temp[i] != '\0')
	{
		(info->basic_information)[i] = temp[i];
		i++;
	}
	(info->basic_information)[i] = '\0';
	info->len_buf = i;
	free(temp);
}

void					writer_base(t_info *info, char *line)
{
	int			i;
	int			j;

	i = 0;
	j = ft_strlen(line);
	while ((info->len_buf) + j + 2 > (info->buf_size))
		ft_remalloc(info);
	while (j > i)
	{
		(info->basic_information)[info->len_buf++] = line[i];
		++i;
	}
	(info->basic_information)[info->len_buf++] = '\n';
	(info->basic_information)[info->len_buf] = '\0';
}
