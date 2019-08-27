/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:14:14 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 20:05:12 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *ptr;

	if (!(ptr = (char *)malloc(sizeof(*ptr) * size)) || size + 1 == 0)
		return (NULL);
	ft_bzero(ptr, size);
	return ((void *)ptr);
}
