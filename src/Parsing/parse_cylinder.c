/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:36:48 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/11 17:22:22 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_cy_size(char **tokens, t_cylinder *cy)
{
	if (!parse_double(tokens[3], &cy->radius)
		|| !parse_double(tokens[4], &cy->height)
		|| cy->radius <= 0.0 || cy->height <= 0.0)
		return (0);
	cy->radius /= 2.0;
	return (1);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	char		**tokens;
	t_object	obj;

	tokens = ft_split_spaces(line);
	if (matrix_length(tokens) != 6)
		return (free_matrix(tokens), rt_error("Invalid cylinder format"));
	obj.type = CYLINDER;
	if (!parse_vec3(tokens[1], &obj.shape.cylinder.center))
		return (free_matrix(tokens),
			rt_error("Cylinder center must have 3 values (x,y,z)"));
	if (!parse_direction(tokens[2], &obj.shape.cylinder.axis))
		return (free_matrix(tokens),
			rt_error("Cylinder axis must be in [-1,1], not all zero"));
	if (!parse_cy_size(tokens, &obj.shape.cylinder))
		return (free_matrix(tokens),
			rt_error("Cylinder diameter and height must be positive"));
	if (!parse_color(tokens[5], &obj.color))
		return (free_matrix(tokens),
			rt_error("RGB color values must be between 0 and 255"));
	free_matrix(tokens);
	if (!add_object(scene, obj))
		return (rt_error("Memory allocation failed"));
	return (1);
}
