/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:40:14 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/10 14:46:18 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Ray:    P(t) = O + t * D
** Sphere: |P - C|^2 = r^2   (all points at distance r from center C)
** Substitute the ray into the sphere and expand, with oc = O - C:
**   (D.D) t^2  +  2 (oc.D) t  +  (oc.oc - r^2)  =  0
** A plain quadratic a t^2 + b t + c = 0 whose discriminant decides:
**   disc < 0  -> the line misses the sphere entirely
**   disc = 0  -> grazing hit (tangent), one root
**   disc > 0  -> the line crosses: two roots, entry and exit
** We want the SMALLEST t above EPSILON: try the near root first; if
** it is behind us (negative) or too close, try the far one -- that
** second chance is what makes a camera INSIDE the sphere still see
** its inner surface (subject: insides must be handled correctly).
*/
int	intersect_sphere(t_ray ray, t_object *obj, t_hit *hit)
{
	t_vector	oc;
	double		abc[3];
	double		disc;
	double		t;

	oc = sous_vec(ray.origin, obj->shape.sphere.center);
	abc[0] = dot_product(ray.direction, ray.direction);
	abc[1] = 2.0 * dot_product(oc, ray.direction);
	abc[2] = dot_product(oc, oc)
		- obj->shape.sphere.radius * obj->shape.sphere.radius;
	disc = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (disc < 0.0)
		return (0);
	t = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		t = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	if (t < EPSILON)
		return (0);
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->normal = normalization(sous_vec(hit->point,
				obj->shape.sphere.center));
	hit->object = obj;
	return (1);
}
