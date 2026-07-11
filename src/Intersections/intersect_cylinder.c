/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 19:58:39 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 17:31:14 by edefoy           ###   ########.fr       */
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

/*
** One cap = a DISK: the plane through C + side*(h/2)*A with normal A
** (side = +1 top, -1 bottom), restricted to the points within radius
** of the cap center. Plane math is ticket 2.4's; the radius check
** compares SQUARED lengths (v.v <= r^2) to avoid a sqrt per ray.
** The outward normal of a closed solid: +A on top, -A below.
*/
static int	cap_hit(t_ray ray, t_object *obj, double side, t_hit *hit)
{
	t_cylinder	cy;
	t_vector	cap_c;
	t_vector	v;
	double		denom;
	double		t;

	cy = obj->shape.cylinder;
	cap_c = add_vec(cy.center, mul_vec(cy.axis, side * cy.height / 2.0));
	denom = dot_product(ray.direction, cy.axis);
	if (fabs(denom) < EPSILON)
		return (0);
	t = dot_product(sous_vec(cap_c, ray.origin), cy.axis) / denom;
	if (t < EPSILON)
		return (0);
	v = sous_vec(ray_at(ray, t), cap_c);
	if (dot_product(v, v) > cy.radius * cy.radius)
		return (0);
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->normal = mul_vec(cy.axis, side);
	hit->object = obj;
	return (1);
}

static void	keep_closest(t_hit *best, t_hit *cand, int *found)
{
	if (!*found || cand->t < best->t)
	{
		*best = *cand;
		*found = 1;
	}
}

/*
** The finite cylinder is body + top cap + bottom cap: collect every
** valid candidate and keep the smallest t. Only the NEAREST valid
** body root can matter: any valid cap hit lies laterally inside the
** tube, hence between the tube roots, so it can never be beaten by
** the far root when the near one is valid.
*/
int	intersect_cylinder(t_ray ray, t_object *obj, t_hit *hit)
{
	double	roots[2];
	t_hit	cand;
	int		found;

	found = 0;
	if (solve_tube(ray, obj->shape.cylinder, roots)
		&& (body_hit(ray, obj, roots[0], &cand)
			|| body_hit(ray, obj, roots[1], &cand)))
		keep_closest(hit, &cand, &found);
	if (cap_hit(ray, obj, 1.0, &cand))
		keep_closest(hit, &cand, &found);
	if (cap_hit(ray, obj, -1.0, &cand))
		keep_closest(hit, &cand, &found);
	return (found);
}
