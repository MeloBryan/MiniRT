/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:23 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/09 16:10:48 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	normalization(t_vector A)
{
	t_vector	res;
	double		length;

	length = vec_length(A);
	res.x = A.x / length;
	res.y = A.y / length;
	res.z = A.z / length;
	return (res);
}
