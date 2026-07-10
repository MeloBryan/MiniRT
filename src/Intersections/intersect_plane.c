/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:48:56 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/10 19:59:58 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Plane: (P - P0) . N = 0   (P0 = anchor point, N = unit normal)
** Substitute P(t) = O + t * D and solve -- t comes out LINEAR:
**   t = ((P0 - O) . N) / (D . N)
** Guard: if D.N is ~0 the ray is parallel to the plane; the division
** would explode, and geometrically a zero-thickness plane seen
** edge-on is invisible -> miss (also covers a ray lying IN it).
** Normal: a plane has no inside/outside, so its stored normal's
** orientation is arbitrary. We flip it to face the incoming ray
** (D . N > 0 means it points away from the viewer), so both sides
** of the infinite plane render and shade correctly.
*/
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
