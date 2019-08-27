/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:58:02 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 15:37:41 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (size + 1 == 0)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	str = (char *)ft_memset(str, '\0', size + 1);
	return (str);
}
