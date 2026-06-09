/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:21:01 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/08 15:02:25 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

int	main(int ac, char **av)
{
	t_data	data;
	(void)av;
	(void)ac;

	ft_bzero(&data, sizeof(t_data));
	data.mlx = NULL;
	data.win = NULL;
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
