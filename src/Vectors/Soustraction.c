/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Soustraction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:09:21 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/09 16:10:20 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	sous_vec(t_vector A, t_vector B)
{
	t_vector	res;

	res.x = B.x - A.x;
	res.y = B.y - A.y;
	res.z = B.z - A.z;
	return (res);
}
