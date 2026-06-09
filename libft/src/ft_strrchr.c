/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:11:26 by bmelo             #+#    #+#             */
/*   Updated: 2025/11/21 11:33:20 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	char	ch;
	char	*last;

	last = NULL;
	ch = (char) c;
	while (*str)
	{
		if (*str == ch)
			last = str;
		str++;
	}
	if (ch == '\0')
		return ((char *) str);
	return ((char *) last);
}
