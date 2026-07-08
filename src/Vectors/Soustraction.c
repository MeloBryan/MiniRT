/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Soustraction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:21 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/08 14:33:09 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	sous_vec(t_vector A, t_vector B)
{
	t_vector	res;

	res.x = A.x - B.x;
	res.y = A.y - B.y;
	res.z = A.z - B.z;
	return (res);
}
