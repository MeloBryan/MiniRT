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

static int	valid_direction(t_vector dir)
{
	if (dir.x < -1.0 || dir.x > 1.0 || dir.y < -1.0 || dir.y > 1.0
		|| dir.z < -1.0 || dir.z > 1.0)
		return (0);
	if (dir.x == 0.0 && dir.y == 0.0 && dir.z == 0.0)
		return (0);
	return (1);
}

int	parse_camera(char *line, t_data *data)
{
	char	**tokens;

	if (data->camera_already_set == 1)
		return (rt_error("Multiple camera detected"));
	tokens = ft_split_spaces(line);
	if (matrix_length(tokens) != 4)
		return (free_matrix(tokens), rt_error("Invalid camera format"));
	if (!parse_vec3(tokens[1], &data->cam_pos))
		return (free_matrix(tokens),
			rt_error("POSITION must have 3 values (x,y,z)"));
	if (!parse_vec3(tokens[2], &data->cam_dir))
		return (free_matrix(tokens),
			rt_error("DIRECTION must have 3 values (x,y,z)"));
	if (!valid_direction(data->cam_dir))
		return (free_matrix(tokens),
			rt_error("Invalid direction value(must be between -1 and 1)"));
	data->cam_fov = ft_atof(tokens[3]);
	if (data->cam_fov < 0 || data->cam_fov > 180)
		return (free_matrix(tokens),
			rt_error("FOV value must be between 0 and 180"));
	data->camera_already_set = 1;
	return (free_matrix(tokens), 1);
}
