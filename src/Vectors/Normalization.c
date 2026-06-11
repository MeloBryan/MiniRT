/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:23 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/12 00:35:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	normalization(t_vector A)
{
	t_vector	res;
	double		length;

	length = vec_length(A);
	if (length == 0)
		return (A);
	res.x = A.x / length;
	res.y = A.y / length;
	res.z = A.z / length;
	return (res);
}
