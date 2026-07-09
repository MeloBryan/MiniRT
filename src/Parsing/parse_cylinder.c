/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:36:48 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/09 14:38:32 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	obj.shape.cylinder.radius = ft_atof(tokens[3]) / 2.0;
	obj.shape.cylinder.height = ft_atof(tokens[4]);
	if (obj.shape.cylinder.radius <= 0.0 || obj.shape.cylinder.height <= 0.0)
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