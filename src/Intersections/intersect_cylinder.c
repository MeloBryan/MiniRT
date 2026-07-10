/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 19:58:39 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/10 19:59:31 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Infinite tube around axis (C, A), A unit length:
**   dist^2(P, axis) = |X|^2 - (X.A)^2 = r^2   with X = P - C
** Substituting X = oc + t*D gives a quadratic whose coefficients are
** the sphere's, each corrected by "minus its along-axis component":
**   a = D.D - (D.A)^2          (= |D_perp|^2, 0 if ray || axis)
**   b = 2 (D.oc - (D.A)(oc.A))
**   c = oc.oc - (oc.A)^2 - r^2
** Returns both roots (entry, exit) of the INFINITE tube; the height
** clamp happens per-root in body_hit.
*/
static int	solve_tube(t_ray ray, t_cylinder cy, double roots[2])
{
	t_vector	oc;
	double		dots[2];
	double		abc[3];
	double		disc;

	oc = sous_vec(ray.origin, cy.center);
	dots[0] = dot_product(ray.direction, cy.axis);
	dots[1] = dot_product(oc, cy.axis);
	abc[0] = dot_product(ray.direction, ray.direction) - dots[0] * dots[0];
	abc[1] = 2.0 * (dot_product(ray.direction, oc) - dots[0] * dots[1]);
	abc[2] = dot_product(oc, oc) - dots[1] * dots[1]
		- cy.radius * cy.radius;
	if (abc[0] < EPSILON)
		return (0);
	disc = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (disc < 0.0)
		return (0);
	roots[0] = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	roots[1] = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	return (1);
}

/*
** Validates one tube root: in front of the ray AND within the finite
** height. m = X.A is the hit's coordinate along the axis, measured
** from the center (the axis MIDPOINT per the subject), so the body
** spans m in [-h/2, +h/2]. The normal is radial: from the foot of
** the perpendicular F = C + m*A toward the hit point.
*/
static int	body_hit(t_ray ray, t_object *obj, double t, t_hit *hit)
{
	t_cylinder	cy;
	double		m;
	t_vector	foot;

	cy = obj->shape.cylinder;
	if (t < EPSILON)
		return (0);
	m = dot_product(sous_vec(ray_at(ray, t), cy.center), cy.axis);
	if (fabs(m) > cy.height / 2.0)
		return (0);
	hit->t = t;
	hit->point = ray_at(ray, t);
	foot = add_vec(cy.center, mul_vec(cy.axis, m));
	hit->normal = normalization(sous_vec(hit->point, foot));
	hit->object = obj;
	return (1);
}

int	intersect_cylinder(t_ray ray, t_object *obj, t_hit *hit)
{
	double	roots[2];

	if (!solve_tube(ray, obj->shape.cylinder, roots))
		return (0);
	if (body_hit(ray, obj, roots[0], hit))
		return (1);
	return (body_hit(ray, obj, roots[1], hit));
}
