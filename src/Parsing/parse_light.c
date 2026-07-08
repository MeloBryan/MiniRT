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

int	parse_light(char *line, t_data *data)
{
	char	**tokens;

	if (data->light_already_set == 1)
		return (rt_error("Multiple light detected"));
	tokens = ft_split_spaces(line);
	if (matrix_length(tokens) != 4)
		return (free_matrix(tokens), rt_error("Invalid light format"));
	if (!parse_vec3(tokens[1], &data->light_pos))
		return (free_matrix(tokens),
			rt_error("POSITION must have 3 values (x,y,z)"));
	data->light_ratio = ft_atof(tokens[2]);
	if (data->light_ratio < 0.0 || data->light_ratio > 1.0)
		return (free_matrix(tokens),
			rt_error("Invalid light ratio value(must be between 0 and 1)"));
	if (!parse_rgb(tokens[3], &data->light_color))
		return (free_matrix(tokens),
			rt_error("RGB color values must be between 0 and 255"));
	data->light_already_set = 1;
	return (free_matrix(tokens), 1);
}
