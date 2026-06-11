/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 17:26:02 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/11 23:47:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "miniRT.h"

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_vector	cam_pos;

	int			max_iterations;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			key[65536];
	double		zoom;
}				t_data;

void	close_win(t_data *data);
void	open_win(t_data *data);
void	handle_input(int key, t_data *data);
void	render_scene(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_ray	ray_init(t_vector screen, t_data *data);

#endif
