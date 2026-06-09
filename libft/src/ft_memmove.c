/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:48:33 by bmelo             #+#    #+#             */
/*   Updated: 2025/11/21 11:34:03 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char			*p1;
	const unsigned char		*p2;

	p1 = (unsigned char *) dest;
	p2 = (const unsigned char *) src;
	if (!dest && !src)
		return (NULL);
	if (p1 > p2)
		while (size-- > 0)
			p1[size] = p2[size];
	else
		ft_memcpy(dest, src, size);
	return (dest);
}
