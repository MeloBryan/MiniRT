/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:57:25 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/09 13:15:53 by edefoy           ###   ########.fr       */
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
