/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 17:45:34 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 17:46:57 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Selection model: data->selected picks the transform target.
**   0 = camera, 1 = light, 2..N = objects in .rt file order.
** All shape structs BEGIN with their position vector and (for plane
** and cylinder) have their direction as second member; C guarantees
** structs in a union share their common initial sequence, so one
** member access covers every type -- no switch on the tag needed.
*/
static t_object	*target_object(t_data *data)
{
	t_object	*obj;
	int			i;

	obj = data->scene.objects;
	i = data->selected - 2;
	while (obj && i > 0)
	{
		obj = obj->next;
		i--;
	}
	return (obj);
}

static t_vector	*target_position(t_data *data)
{
	t_object	*obj;

	if (data->selected == 0)
		return (&data->scene.camera.position);
	if (data->selected == 1)
		return (&data->scene.light.position);
	obj = target_object(data);
	if (!obj)
		return (NULL);
	return (&obj->shape.sphere.center);
}

/*
** Rotation targets only things that HAVE an orientation: the camera
** direction, a plane normal, a cylinder axis. Spheres and lights
** cannot be rotated (subject). Unselected/overflow: NULL, no-op.
*/
static t_vector	*target_direction(t_data *data)
{
	t_object	*obj;

	if (data->selected == 0)
		return (&data->scene.camera.direction);
	if (data->selected == 1)
		return (NULL);
	obj = target_object(data);
	if (!obj || obj->type == SPHERE)
		return (NULL);
	return (&obj->shape.plane.normal);
}

void	translate_target(t_data *data, t_vector delta)
{
	t_vector	*pos;

	pos = target_position(data);
	if (!pos)
		return ;
	*pos = add_vec(*pos, delta);
}

void	rotate_target(t_data *data, char axis, double deg)
{
	t_vector	*dir;

	dir = target_direction(data);
	if (!dir)
		return ;
	if (axis == 'x')
		*dir = rot_x(*dir, deg * M_PI / 180.0);
	else
		*dir = rot_y(*dir, deg * M_PI / 180.0);
	*dir = normalization(*dir);
}
