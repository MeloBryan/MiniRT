/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:21:01 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/09 13:37:02 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (rt_error("Usage: ./MiniRT <scene.rt>"), 1);
	ft_bzero(&data, sizeof(t_data));
	if (!parse_file(argv[1], &data.scene))
		return (free_objects(&data.scene), 1);
	open_win(&data);
	free_data(&data);
	return (0);
}
