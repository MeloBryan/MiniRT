/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:13:35 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/08 15:22:21 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "vector.h"

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_basis
{
	t_vector	f;
	t_vector	r;
	t_vector	u;
}				t_basis;

typedef struct s_camera
{
	t_vector	position;
	t_vector	orientation;
	double		fov;
}				t_camera;

typedef struct s_sphere
{
	t_vector	center;
	double		diametre;
	double		radius;
	t_vector	color;
}				t_sphere;

#endif
