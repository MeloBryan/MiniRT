/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:35:52 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/10 14:37:52 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "structures.h"

# define EPSILON 1e-6

t_vector	ray_at(t_ray ray, double t);
int			intersect_sphere(t_ray ray, t_object *obj, t_hit *hit);

#endif