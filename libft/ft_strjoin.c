/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:02:48 by bdudley           #+#    #+#             */
/*   Updated: 2019/02/22 16:48:26 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s1 == NULL || s2 == NULL ||
			(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL ||
			(str = ft_strcpy(str, s1)) == NULL ||
			(str = ft_strcat(str, s2)) == NULL)
		return (NULL);
	return (str);
}
