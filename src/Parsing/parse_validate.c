/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 17:18:58 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 17:22:03 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_valid_double(char *str)
{
	int	i;
	int	digits;

	i = 0;
	digits = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		i++;
		digits++;
	}
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		i++;
		digits++;
	}
	return (digits > 0 && str[i] == '\0');
}

int	is_valid_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	return (str[i] == '\0');
}

int	parse_double(char *token, double *out)
{
	if (!is_valid_double(token))
		return (0);
	*out = ft_atof(token);
	return (1);
}
