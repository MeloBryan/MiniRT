/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:16:02 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 15:16:02 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_light(char *line, t_scene *scene)
{
	char	**tokens;

	if (scene->light_set == 1)
		return (rt_error("Multiple light detected"));
	tokens = ft_split_spaces(line);
	if (matrix_length(tokens) != 4)
		return (free_matrix(tokens), rt_error("Invalid light format"));
	if (!parse_vec3(tokens[1], &scene->light.position))
		return (free_matrix(tokens),
			rt_error("POSITION must have 3 values (x,y,z)"));
	if (!parse_double(tokens[2], &scene->light.ratio)
		|| scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		return (free_matrix(tokens),
			rt_error("Invalid light ratio value(must be between 0 and 1)"));
	if (!parse_color(tokens[3], &scene->light.color))
		return (free_matrix(tokens),
			rt_error("RGB color values must be between 0 and 255"));
	scene->light_set = 1;
	return (free_matrix(tokens), 1);
}
