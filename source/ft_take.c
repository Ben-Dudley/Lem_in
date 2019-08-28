/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharrold <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 17:45:21 by hharrold          #+#    #+#             */
/*   Updated: 2019/08/08 17:45:24 by hharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h.h"

static char			*ft_copyread(const int fd)
{
	char				str_buf[2];
	char				*str_text;
	char				*str_free;
	int					ret;

	if (!(str_text = (char*)malloc(sizeof(char) + 1 + 1)))
		return (NULL);
	*str_text = '\0';
	if ((ret = read(fd, str_buf, 0) < 0))
		return (NULL);
	while ((ret = read(fd, str_buf, 1)) > 0)
	{
		if (str_buf[ret - 1] == '\n')
			break ;
		str_buf[ret] = '\0';
		str_free = str_text;
		str_text = ft_strjoin(str_text, str_buf);
		free(str_free);
	}
	return (str_text);
}

int					ft_take(const int fd, char **line)
{
	static char			*buf[0];

	if (!(buf[fd] = ft_copyread(fd)))
		return (-1);
	*line = buf[fd];
	return (1);
}
