/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:59:22 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 17:23:09 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere(char *line, t_scene *scene)
{
	char		**tokens;
	t_object	obj;

	tokens = ft_split_spaces(line);
	if (matrix_length(tokens) != 4)
		return (free_matrix(tokens), rt_error("Invalid sphere format"));
	obj.type = SPHERE;
	if (!parse_vec3(tokens[1], &obj.shape.sphere.center))
		return (free_matrix(tokens),
			rt_error("Sphere center must have 3 values (x,y,z)"));
	if (!parse_double(tokens[2], &obj.shape.sphere.radius)
		|| obj.shape.sphere.radius <= 0.0)
		return (free_matrix(tokens),
			rt_error("Sphere diameter must be a positive value"));
	obj.shape.sphere.radius /= 2.0;
	if (!parse_color(tokens[3], &obj.color))
		return (free_matrix(tokens),
			rt_error("RGB color values must be between 0 and 255"));
	free_matrix(tokens);
	if (!add_object(scene, obj))
		return (rt_error("Memory allocation failed"));
	return (1);
}
