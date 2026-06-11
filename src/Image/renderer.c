/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:41:00 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/11 23:57:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_scene(t_data *data)
{
	int			x;
	int			y;
	double		aspect_ratio;
	t_vector	screen;
	t_ray		ray;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	y = -1;
	while (y++ < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
		{
			screen.x = (2.0 * ((double)x / WIDTH) - 1.0) * aspect_ratio;
			screen.y = 1.0 + 2.0 * ((double)y / HEIGHT);
			ray = ray_init(screen, data);
			int r = (int)((ray.direction.x + 1.0) * 127.5);
			int g = (int)((ray.direction.y + 1.0) * 127.5);
			int b = (int)((ray.direction.z + 1.0) * 127.5);
			int color = (r << 16) | (g << 8) | b;
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}

t_ray	ray_init(t_vector screen, t_data *data)
{
	t_ray	ray;

	ray.origin = data->cam_pos;
	ray.direction.x = screen.x;
	ray.direction.y = screen.y;
	ray.direction.z = 1.0;
	ray.direction = normalization(ray.direction);
	return (ray);
}

t_vector	update_camera_vectors(t_vector camera, t_data *data)
{
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	t_vector	world_up;

	forward = normalization(data->cam_pos);
	world_up.x = 0.0;
	world_up.y = 1.0;
	world_up.z = 0.0;
	right = normalization(cross_vec(world_up, forward));
	up = cross_vec(forward, right);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
