/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:07:08 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/08 16:18:21 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_vector	sous_vec(t_vector A, t_vector B)
{
	t_vector	res;

	res.x = B.x - A.x;
	res.y = B.y - A.y;
	res.z = B.z - A.z;
	return (res);
}

t_vector	add_vec(t_vector A, t_vector B)
{
	t_vector	res;

	res.x = B.x + A.x;
	res.y = B.y + A.y;
	res.z = B.z + A.z;
	return (res);
}
