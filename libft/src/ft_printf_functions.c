/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:19:06 by bmelo             #+#    #+#             */
/*   Updated: 2026/02/21 10:46:36 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_p(unsigned long long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (write (1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += ft_putnbr_base(nb, HEXA_LOW);
	return (count);
}

void	format_handled(char c, va_list args, int *count)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		*count += 1;
	}
	else if (c == 's')
		*count += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		*count += print_p(va_arg(args, unsigned long long));
	else if (c == 'd' || c == 'i')
		*count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		*count += ft_putnbr_base(va_arg(args, unsigned int), DECIMAL);
	else if (c == 'x')
		*count += ft_putnbr_base(va_arg(args, unsigned int), HEXA_LOW);
	else if (c == 'X')
		*count += ft_putnbr_base(va_arg(args, unsigned int), HEXA_UP);
	else if (c == '%')
		*count += ft_putchar('%');
}
