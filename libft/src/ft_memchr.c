/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:45:15 by bmelo             #+#    #+#             */
/*   Updated: 2025/11/21 11:34:13 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	size_t					i;
	const unsigned char		*sh;

	i = 0;
	sh = (unsigned char const *)s;
	while (i < size)
	{
		if (sh[i] == (unsigned char)c)
			return ((void *) sh + i);
		i++;
	}
	return (NULL);
}
