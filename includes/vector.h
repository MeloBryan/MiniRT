/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:41:12 by bmelo             #+#    #+#             */
/*   Updated: 2026/06/10 05:10:03 by marvin           ###   ########.fr       */
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

t_vector	add_vec(t_vector A, t_vector B);
t_vector	sous_vec(t_vector A, t_vector B);
t_vector	mul_vec(t_vector A, double i);
double		dot_product(t_vector A, t_vector B);
double		vec_length(t_vector A);
t_vector	normalization(t_vector A);

#endif
