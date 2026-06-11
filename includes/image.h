/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 17:26:02 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/12 00:20:40 by marvin           ###   ########.fr       */
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
	t_vector	cam_dir;

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
t_ray	ray_init(t_vector screen, t_vector r, t_vector u, t_vector f, t_data *data);
void	update_camera_vectors(t_vector *f, t_vector *r, t_vector *u, t_data *data);

#endif
