/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 17:43:38 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 17:44:53 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	rot_x(t_vector v, double a)
{
	t_vector	res;

	res.x = v.x;
	res.y = v.y * cos(a) - v.z * sin(a);
	res.z = v.y * sin(a) + v.z * cos(a);
	return (res);
}

t_vector	rot_y(t_vector v, double a)
{
	t_vector	res;

	res.x = v.x * cos(a) + v.z * sin(a);
	res.y = v.y;
	res.z = -v.x * sin(a) + v.z * cos(a);
	return (res);
}
