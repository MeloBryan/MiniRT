/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayon.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:16:11 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/10 14:46:58 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	ray_init(t_vector screen, t_basis basis, t_data *data)
{
	t_ray	ray;

	ray.origin = data->scene.camera.position;
	ray.direction.x = (screen.x * basis.r.x) + (screen.y * basis.u.x)
		+ basis.f.x;
	ray.direction.y = (screen.x * basis.r.y) + (screen.y * basis.u.y)
		+ basis.f.y;
	ray.direction.z = (screen.x * basis.r.z) + (screen.y * basis.u.z)
		+ basis.f.z;
	ray.direction = normalization(ray.direction);
	return (ray);
}

void	update_camera_vectors(t_basis *basis, t_data *data)
{
	t_vector	world_up;

	basis->f = normalization(data->scene.camera.direction);
	world_up.x = 0.0;
	world_up.y = 1.0;
	world_up.z = 0.0;
	basis->r = normalization(cross_vec(basis->f, world_up));
	basis->u = cross_vec(basis->f, basis->r);
}

t_vector	ray_at(t_ray ray, double t)
{
	return (add_vec(ray.origin, mul_vec(ray.direction, t)));
}
