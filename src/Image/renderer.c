/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:41:00 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/12 00:34:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_scene(t_data *data)
{
	int			x;
	int			y;
	double		aspect_ratio;
	t_vector	f;
	t_vector	u;
	t_vector	r;
	t_vector	screen;
	t_ray		ray;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	update_camera_vectors(&f, &r, &u, data);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			screen.x = (2.0 * ((double)x / WIDTH) - 1.0) * aspect_ratio;
			screen.y = 1.0 + 2.0 * ((double)y / HEIGHT);
			ray = ray_init(screen, r, u, f, data);
			int re = (int)((ray.direction.x + 1.0) * 127.5);
			int g = (int)((ray.direction.y + 1.0) * 127.5);
			int b = (int)((ray.direction.z + 1.0) * 127.5);
			int color = (re << 16) | (g << 8) | b;
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

t_ray	ray_init(t_vector screen, t_vector r, t_vector u, t_vector f, t_data *data)
{
	t_ray	ray;

	ray.origin = data->cam_pos;
	ray.direction.x = (screen.x * r.x) + (screen.y * u.x) + f.x;
	ray.direction.y = (screen.x * r.y) + (screen.y * u.y) + f.y;
	ray.direction.z= (screen.x * r.z) + (screen.y * u.z) + f.z;
	ray.direction = normalization(ray.direction);
	return (ray);
}

void	update_camera_vectors(t_vector *f, t_vector *r, t_vector *u, t_data *data)
{
	t_vector	world_up;

	*f = normalization(data->cam_dir);
	world_up.x = 0.0;
	world_up.y = 1.0;
	world_up.z = 0.0;
	*r = normalization(cross_vec(world_up, *f));
	*u = cross_vec(*f, *r);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
