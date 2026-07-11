/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 15:53:42 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 16:05:43 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Shading needs the normal on the side the viewer sees. Solids
** report their geometric OUTWARD normal; when the camera is inside
** (looking at an inner wall) that normal points away from us and
** Lambert would black the surface out. If N and the ray direction
** agree (dot > 0), flip. Planes already arrive viewer-facing; the
** check is then a no-op.
*/
static t_vector	facing_normal(t_hit *hit, t_ray ray)
{
	if (dot_product(hit->normal, ray.direction) > 0.0)
		return (mul_vec(hit->normal, -1.0));
	return (hit->normal);
}

/*
** Can this point see the light? Fire a ray FROM the hit point TOWARD
** the light through the same hit_anything used for camera rays --
** shadows cost zero new intersection code. Two bounds on t:
**   t > EPSILON  (inside every intersect_*): the ray starts ON a
**     surface; without it, it re-hits its own surface at t ~ 0 and
**     the image speckles with "shadow acne"
**   t < light_dist: an occluder BEYOND the light does not block it.
** to_light must be unit length so t is a world distance comparable
** to light_dist.
*/
static int	in_shadow(t_scene *scene, t_vector point, t_vector to_light,
		double light_dist)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.origin = point;
	shadow_ray.direction = to_light;
	if (!hit_anything(shadow_ray, scene, &hit))
		return (0);
	return (hit.t < light_dist);
}

/*
** Mandatory lighting = ambient + diffuse + hard shadows:
**   ambient: ratio * ambient_color -- floor of illumination, the
**     subject's "objects are never completely in the dark"
**   diffuse (Lambert): light_ratio * max(0, N.L); skipped when the
**     point is shadowed, leaving ambient only. The shadow ray is
**     fired only when diff > 0: a surface facing away is dark anyway.
** The summed light is applied per channel to the object color.
*/
t_color	shade_hit(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_vector	to_light;
	t_color		light_sum;
	double		light_dist;
	double		diff;

	light_sum = mul_vec(scene->ambient.color, scene->ambient.ratio);
	to_light = sous_vec(scene->light.position, hit->point);
	light_dist = vec_length(to_light);
	to_light = normalization(to_light);
	diff = scene->light.ratio
		* dot_product(facing_normal(hit, ray), to_light);
	if (diff > 0.0 && !in_shadow(scene, hit->point, to_light, light_dist))
	{
		light_sum.x += diff;
		light_sum.y += diff;
		light_sum.z += diff;
	}
	return (color_mul(light_sum, hit->object->color));
}
