/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:39:58 by bmelo             #+#    #+#             */
/*   Updated: 2025/11/21 11:34:23 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*dest;
	int			count;
	int			i;
	long		nb;

	count = count_size(n);
	nb = n;
	if (n < 0 || count == 0)
		count++;
	dest = ft_calloc(sizeof(char), (count + 1));
	if (!dest)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		dest[0] = '-';
		i++;
	}
	while (count > i)
	{
		dest[--count] = (nb % 10) + '0';
		nb /= 10;
	}
	return (dest);
}
