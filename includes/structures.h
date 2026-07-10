/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 16:13:35 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/10 14:35:12 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "vector.h"

/*
** A color is a vector: x = red, y = green, z = blue.
** Channels are stored NORMALIZED in [0.0, 1.0] (parsed value / 255).
** Lighting math then becomes plain vector math; we convert back to a
** packed 0xRRGGBB int only once per pixel, at MLX write time.
*/
typedef t_vector	t_color;

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

typedef struct s_ambient
{
	double		ratio;
	t_color		color;
}				t_ambient;

typedef struct s_camera
{
	t_vector	position;
	t_vector	direction;
	double		fov;
}				t_camera;

typedef struct s_light
{
	t_vector	position;
	double		ratio;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	axis;
	double		radius;
	double		height;
}				t_cylinder;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}				t_obj_type;

/*
** Tagged union: 'type' says which member of 'shape' is meaningful.
** All shapes share the same memory; the union is as big as the largest
** member only. One list node type covers every object kind.
*/
typedef union u_shape
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}				t_shape;

typedef struct s_object
{
	t_obj_type		type;
	t_color			color;
	t_shape			shape;
	struct s_object	*next;
}				t_object;

/*
** The result of a successful ray/object intersection.
** t is the distance along the ray (P = origin + t * direction);
** point is that position in world space; normal is the unit surface
** normal at that point; object identifies what was hit (its color).
*/
typedef struct s_hit
{
	double		t;
	t_vector	point;
	t_vector	normal;
	t_object	*object;
}				t_hit;

/*
** The full scene description, filled by parsing, read by rendering.
** The *_set flags enforce "declared exactly once" for A, C and L.
*/
typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
	int			ambient_set;
	int			camera_set;
	int			light_set;
}				t_scene;

#endif
