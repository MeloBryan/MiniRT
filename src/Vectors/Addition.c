/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:54 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/08 15:27:08 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	add_vec(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}
