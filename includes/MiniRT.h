/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:21:32 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/08 16:11:44 by bmelo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "Keys.h"
# include "../minilibx_linux/mlx.h"
# include "../libft/includes/libft.h"

# define WIDTH 800
# define HEIGHT 800

typedef struct s_data
{
	void	*mlx;
	void	*win;
	double	x;
	double	y;
	double	z;

	int		max_iterations;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int		key[65536];
	double	zoom;
}				t_data;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

//Windows Functions
void	close_win(t_data *data);
void	open_win(t_data *data);
//Input Handler
void	handle_input(int key, t_data *data);

#endif
