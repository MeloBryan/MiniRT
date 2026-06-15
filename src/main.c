/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:21:01 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/16 01:10:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		printf("Error\nUsage: .:MiniRT <scene.rt>\n");
		return (0);
	}
	ft_bzero(&data, sizeof(t_data));
	data.mlx = NULL;
	data.win = NULL;
	if (parse_file(av[1], &data) == 0)
		return (1);
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
