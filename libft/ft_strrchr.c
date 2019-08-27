/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 22:15:01 by bdudley           #+#    #+#             */
/*   Updated: 2018/12/06 21:25:18 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ptr;

	ptr = NULL;
	while (*s != '\0')
	{
		if ((unsigned char)(*s) == (unsigned char)c)
			ptr = (char *)s;
		s++;
	}
	if (*s == (unsigned char)c)
		ptr = (char *)s;
	return (ptr);
}
