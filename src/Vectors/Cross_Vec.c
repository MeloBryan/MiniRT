/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cross_Vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:20:01 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 15:20:01 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	cross_vec(t_vector a, t_vector b)
{
	t_vector	res;

	res.x = (a.y * b.z) - (a.z * b.y);
	res.y = (a.z * b.x) - (a.x * b.z);
	res.z = (a.x * b.y) - (a.y * b.x);
	return (res);
}
