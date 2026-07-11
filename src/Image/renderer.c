/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:17:46 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 16:07:20 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	render_pixel(t_data *data, t_basis basis, int x, int y)
{
	t_vector	screen;
	t_ray		ray;
	t_hit		hit;

	screen.x = (2.0 * ((double)x / WIDTH) - 1.0) * basis.half_w;
	screen.y = (1.0 - 2.0 * ((double)y / HEIGHT)) * basis.half_h;
	screen.z = 0.0;
	ray = ray_init(screen, basis, data);
	if (hit_anything(ray, &data->scene, &hit))
		my_mlx_pixel_put(data, x, y,
			color_to_int(shade_hit(&data->scene, ray, &hit)));
	else
		my_mlx_pixel_put(data, x, y, 0x000000);
}

void	render_scene(t_data *data)
{
	t_basis	basis;
	int		x;
	int		y;

	update_camera_vectors(&basis, data);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel(data, basis, x, y);
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
