/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:48:56 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/10 15:53:32 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_plane(t_ray ray, t_object *obj, t_hit *hit)
{
	double	denom;
	double	t;

	denom = dot_product(ray.direction, obj->shape.plane.normal);
	if (fabs(denom) < EPSILON)
		return (0);
	t = dot_product(sous_vec(obj->shape.plane.point, ray.origin),
			obj->shape.plane.normal) / denom;
	if (t < EPSILON)
		return (0);
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->normal = obj->shape.plane.normal;
	if (denom > 0.0)
		hit->normal = mul_vec(hit->normal, -1.0);
	hit->object = obj;
	return (1);
}
