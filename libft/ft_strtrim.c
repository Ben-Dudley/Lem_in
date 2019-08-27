/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:20:30 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 16:51:56 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	int		start;
	int		finish;

	if (s == NULL)
		return (NULL);
	start = 0;
	finish = ft_strlen(s) - 1;
	str = NULL;
	while (s[start] == '\n' || s[start] == '\t' || s[start] == ' ')
		start++;
	while ((s[finish] == '\n' || s[finish] == '\t' ||
				s[finish] == ' ') && finish != 0)
		finish--;
	if (start > finish)
	{
		if ((str = ft_strnew(1)) == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	if ((str = ft_strnew(finish - start + 1)) == NULL ||
			(str = ft_strncpy(str, s + start, finish - start + 1)) == NULL)
		return (NULL);
	return (str);
}
