/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:34:17 by bmelo             #+#    #+#             */
/*   Updated: 2025/11/21 11:33:35 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	result;
	size_t	i;

	i = 0;
	result = 0;
	len_s = ft_strlen(src);
	len_d = ft_strlen(dest);
	if (size > len_d)
		result = len_d + len_s;
	else
		result = len_s + size;
	while (src[i] != '\0' && len_d + 1 < size)
	{
		dest[len_d] = src[i];
		i++;
		len_d++;
	}
	dest[len_d] = '\0';
	return (result);
}
