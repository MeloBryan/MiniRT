/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:27:30 by bmelo             #+#    #+#             */
/*   Updated: 2025/11/14 10:15:19 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (s2[i] == '\0')
		return ((char *) s1);
	while (s1[i] && i < len)
	{
		while (s1[i + j] == s2[j] && s1[i + j] && i + j < len)
		{
			j++;
			if (s2[j] == 0)
				return ((char *) s1 + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
