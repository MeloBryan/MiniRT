/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:21:01 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/12 00:39:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	t_data	data;
	(void)av;
	(void)ac;

	ft_bzero(&data, sizeof(t_data));
	data.mlx = NULL;
	data.win = NULL;
	data.cam_pos.x = 0.0;  data.cam_pos.y = 0.0;  data.cam_pos.z = 0.0;
    data.cam_dir.x = 0.0; data.cam_dir.y = 0.0;  data.cam_dir.z = 1.0;
	open_win(&data);
	if (data.mlx)
	{
		if (data.img)
			mlx_destroy_image(data.mlx, data.img);
		if (data.win)
			mlx_destroy_window(data.mlx, data.win);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
	}
	return (0);
}
