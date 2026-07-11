/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:57:25 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 16:00:38 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Converts a normalized color (channels in [0.0, 1.0]) to the packed
** 0xRRGGBB int that MLX expects. Channels are clamped first: lighting
** sums can push a channel above 1.0, and without the clamp the excess
** would overflow into the neighbouring channel when shifted.
*/
int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(fmin(fmax(color.x, 0.0), 1.0) * 255.0);
	g = (int)(fmin(fmax(color.y, 0.0), 1.0) * 255.0);
	b = (int)(fmin(fmax(color.z, 0.0), 1.0) * 255.0);
	return ((r << 16) | (g << 8) | b);
}

/*
** Per-channel (Hadamard) product: how light TINTS a surface. Each
** channel of the surface reflects only that channel of the incoming
** light: a red object (1,0,0) under white light (1,1,1) stays red;
** under pure blue light (0,0,1) it reflects nothing and goes black.
*/
t_color	color_mul(t_color a, t_color b)
{
	t_color	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}
