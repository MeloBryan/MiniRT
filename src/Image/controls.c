/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 17:47:45 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 17:49:46 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Key map (see keys.h):
**   ESC          quit
**   0            select camera        Q / E   rotate around Y -/+
**   1            select light         R / F   rotate around X +/-
**   2..6         select object 1..5
**   arrows       translate x / y      W / S   translate z +/-
** Every scene change triggers a full re-render of the image, then
** one push to the window. The mlx guard in rerender keeps the whole
** control path testable headless.
*/
static void	rerender(t_data *data)
{
	render_scene(data);
	if (data->mlx)
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

static t_vector	vec(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

static void	handle_translate(int key, t_data *data)
{
	if (key == LEFT)
		translate_target(data, vec(-TR_STEP, 0.0, 0.0));
	else if (key == RIGHT)
		translate_target(data, vec(TR_STEP, 0.0, 0.0));
	else if (key == UP)
		translate_target(data, vec(0.0, TR_STEP, 0.0));
	else if (key == DOWN)
		translate_target(data, vec(0.0, -TR_STEP, 0.0));
	else if (key == W)
		translate_target(data, vec(0.0, 0.0, TR_STEP));
	else if (key == S)
		translate_target(data, vec(0.0, 0.0, -TR_STEP));
}

static void	handle_rotate(int key, t_data *data)
{
	if (key == Q)
		rotate_target(data, 'y', -ROT_STEP);
	else if (key == E)
		rotate_target(data, 'y', ROT_STEP);
	else if (key == R)
		rotate_target(data, 'x', ROT_STEP);
	else if (key == F)
		rotate_target(data, 'x', -ROT_STEP);
}

void	handle_input(int key, t_data *data)
{
	if (key == ESC)
	{
		mlx_loop_end(data->mlx);
		return ;
	}
	if (key >= ZERO && key <= SIX)
		data->selected = key - ZERO;
	else if (key == LEFT || key == RIGHT || key == UP || key == DOWN
		|| key == W || key == S)
		handle_translate(key, data);
	else if (key == Q || key == E || key == R || key == F)
		handle_rotate(key, data);
	else
		return ;
	rerender(data);
}
