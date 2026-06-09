/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:47:29 by bmelo             #+#    #+#             */
/*   Updated: 2025/11/21 11:34:07 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t					i;
	unsigned char			*p1;
	const unsigned char		*p2;

	i = 0;
	p1 = (unsigned char *) dest;
	p2 = (const unsigned char *) src;
	if (!dest && !src)
		return (NULL);
	while (i < size)
	{
		p1[i] = p2[i];
		i++;
	}
	return (p1);
}
