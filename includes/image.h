/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 17:26:02 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/11 15:55:48 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "structures.h"

/*
** t_data now holds ONLY the MLX plumbing, plus the scene it displays.
** Parsers receive &data.scene and cannot touch the window state.
*/
typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			key[65536];
	t_scene		scene;
}				t_data;

void	close_win(t_data *data);
void	open_win(t_data *data);
void	handle_input(int key, t_data *data);
void	render_scene(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_ray	ray_init(t_vector screen, t_basis basis, t_data *data);
void	update_camera_vectors(t_basis *basis, t_data *data);
int		color_to_int(t_color color);
t_color	color_mul(t_color a, t_color b);
t_color	shade_hit(t_scene *scene, t_ray ray, t_hit *hit);

#endif
