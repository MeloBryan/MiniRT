/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:26 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/09 16:10:32 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	mul_vec(t_vector A, double i)
{
	t_vector	res;

	res.x = A.x * i;
	res.y = A.y * i;
	res.z = A.z * i;
	return (res);
}
