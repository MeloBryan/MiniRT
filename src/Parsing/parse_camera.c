/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:15:32 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 15:15:32 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_camera(char *line, t_scene *scene)
{
	char	**tokens;

	if (scene->camera_set == 1)
		return (rt_error("Multiple camera detected"));
	tokens = ft_split_spaces(line);
	if (matrix_length(tokens) != 4)
		return (free_matrix(tokens), rt_error("Invalid camera format"));
	if (!parse_vec3(tokens[1], &scene->camera.position))
		return (free_matrix(tokens),
			rt_error("POSITION must have 3 values (x,y,z)"));
	if (!parse_direction(tokens[2], &scene->camera.direction))
		return (free_matrix(tokens),
			rt_error("DIRECTION must be 3 values in [-1,1], not all zero"));
	scene->camera.fov = ft_atof(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (free_matrix(tokens),
			rt_error("FOV value must be between 0 and 180"));
	scene->camera_set = 1;
	return (free_matrix(tokens), 1);
}
