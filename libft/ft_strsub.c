/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:34:10 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 16:46:56 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str;

	if (s == NULL || (str = ft_strnew(len)) == NULL ||
			(str = ft_strncpy(str, s + start, len)) == NULL)
		return (NULL);
	return (str);
}
