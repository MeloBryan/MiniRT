/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:17:46 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/10 15:15:38 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	background_color(t_ray ray)
{
	int	r;
	int	g;
	int	b;

	r = (int)((ray.direction.x + 1.0) * 127.5);
	g = (int)((ray.direction.y + 1.0) * 127.5);
	b = (int)((ray.direction.z + 1.0) * 127.5);
	return ((r << 16) | (g << 8) | b);
}

static void	render_pixel(t_data *data, t_basis basis, int x, int y)
{
	t_vector	screen;
	t_ray		ray;
	t_hit		hit;

	screen.x = (2.0 * ((double)x / WIDTH) - 1.0)
		* ((double)WIDTH / (double)HEIGHT);
	screen.y = 1.0 - 2.0 * ((double)y / HEIGHT);
	screen.z = 0.0;
	ray = ray_init(screen, basis, data);
	if (hit_anything(ray, &data->scene, &hit))
		my_mlx_pixel_put(data, x, y, color_to_int(hit.object->color));
	else
		my_mlx_pixel_put(data, x, y, background_color(ray));
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
