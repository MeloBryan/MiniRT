/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:17:46 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 15:17:48 by edefoy           ###   ########.fr       */
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

int	hit_sphere_hardcoded(t_ray ray)
{
	t_vector	center;
	t_vector	oc;
	double		a;
	double		b;
	double		c;

	center.x = 0.0;
	center.y = 0.0;
	center.z = 5.0;
	oc = sous_vec(ray.origin, center);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - (1.5 * 1.5);
	return ((b * b) - (4.0 * a * c) >= 0.0);
}

static void	render_pixel(t_data *data, t_basis basis, int x, int y)
{
	t_vector	screen;
	t_ray		ray;

	screen.x = (2.0 * ((double)x / WIDTH) - 1.0)
		* ((double)WIDTH / (double)HEIGHT);
	screen.y = 1.0 - 2.0 * ((double)y / HEIGHT);
	screen.z = 0.0;
	ray = ray_init(screen, basis, data);
	if (hit_sphere_hardcoded(ray))
		my_mlx_pixel_put(data, x, y, 0xFF0000);
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
