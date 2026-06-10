/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:41:00 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/10 05:18:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	render_scene(t_data *data)
{
	int		x;
	int		y;
	double	uv_x;
	double	uv_y;
	double	screen_x;
	double	screen_y;
	double	aspect_ratio;
	t_ray	ray;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		printf("Scanlines remaining : %d\n", (HEIGHT - y));
		while (x < WIDTH)
		{
			uv_x = (double)x / WIDTH;
			uv_y = (double)y / HEIGHT;
			screen_x = (2.0 * uv_x - 1.0) * aspect_ratio;
			screen_y = 1.0 + 2.0 * uv_y;
			ray.origin.x = 0.0;
			ray.origin.y = 0.0;
			ray.origin.z = 0.0;
			ray.direction.x = screen_x;
			ray.direction.y = screen_y;
			ray.direction.z = -1.0;
			ray.direction = normalization(ray.direction);
			//fonction d'appel
			int r = (int)((ray.direction.x + 1.0) * 127.5);
			int g = (int)((ray.direction.y + 1.0) * 127.5);
			int b = (int)((ray.direction.z + 1.0) * 127.5);
			int color = (r << 16) | (g << 8) | b;
			my_mlx_pixel_put(data, x, y, color);
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
