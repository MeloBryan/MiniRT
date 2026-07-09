/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 14:25:26 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/09 14:27:44 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_plane(char *line, t_scene *scene)
{
	char		**tokens;
	t_object	obj;
 
	tokens = ft_split_spaces(line);
	if (matrix_length(tokens) != 4)
		return (free_matrix(tokens), rt_error("Invalid plane format"));
	obj.type = PLANE;
	if (!parse_vec3(tokens[1], &obj.shape.plane.point))
		return (free_matrix(tokens),
			rt_error("Plane point must have 3 values (x,y,z)"));
	if (!parse_direction(tokens[2], &obj.shape.plane.normal))
		return (free_matrix(tokens),
			rt_error("Plane normal must be 3 values in [-1,1], not all zero"));
	if (!parse_color(tokens[3], &obj.color))
		return (free_matrix(tokens),
			rt_error("RGB color values must be between 0 and 255"));
	free_matrix(tokens);
	if (!add_object(scene, obj))
		return (rt_error("Memory allocation failed"));
	return (1);
}
