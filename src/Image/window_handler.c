/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:39:18 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/11 17:48:52 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	open_win(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return ;
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "MiniRT");
	if (!data->win)
		return ;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		return ;
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	render_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_hook(data->win, 2, 1L << 0, (void *)handle_input, data);
	mlx_hook(data->win, 17, 0, (void *)close_win, data);
	mlx_loop(data->mlx);
}

void	close_win(t_data *data)
{
	mlx_loop_end(data->mlx);
}
