/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:00:02 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/10 15:05:52 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	intersect_object(t_ray ray, t_object *obj, t_hit *hit)
{
	if (obj->type == SPHERE)
		return (intersect_sphere(ray, obj, hit));
	return (0);
}

int	hit_anything(t_ray ray, t_scene *scene, t_hit *best)
{
	t_object	*obj;
	t_hit		hit;
	int			found;

	found = 0;
	obj = scene->objects;
	while (obj)
	{
		if (intersect_object(ray, obj, &hit)
			&& (!found || hit.t < best->t))
		{
			*best = hit;
			found = 1;
		}
		obj = obj->next;
	}
	return (found);
}
