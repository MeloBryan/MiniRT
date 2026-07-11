/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:41:12 by bmelo             #+#    #+#             */
/*   Updated: 2026/07/11 17:44:36 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

t_vector	add_vec(t_vector a, t_vector b);
t_vector	sous_vec(t_vector a, t_vector b);
t_vector	mul_vec(t_vector a, double i);
double		dot_product(t_vector a, t_vector b);
double		vec_length(t_vector a);
t_vector	normalization(t_vector a);
t_vector	cross_vec(t_vector a, t_vector b);
t_vector	rot_x(t_vector v, double a);
t_vector	rot_y(t_vector v, double a);

#endif
