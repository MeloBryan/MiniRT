/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:14:08 by edefoy            #+#    #+#             */
/*   Updated: 2026/07/08 15:14:08 by edefoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(char *line, t_data *data)
{
	char	**tokens;

	if (data->ambient_already_set == 1)
		return (rt_error("Multiple Ambient lights detected"));
	tokens = ft_split_spaces(line);
	if (matrix_length(tokens) != 3)
		return (free_matrix(tokens), rt_error("Invalid Ambient light format"));
	data->ambient_ratio = ft_atof(tokens[1]);
	if (data->ambient_ratio < 0.0 || data->ambient_ratio > 1.0)
		return (free_matrix(tokens),
			rt_error("Ambient ratio must be between 0.0 and 1.0"));
	if (!parse_rgb(tokens[2], &data->ambient_color))
		return (free_matrix(tokens),
			rt_error("RGB color values must be between 0 and 255"));
	data->ambient_already_set = 1;
	return (free_matrix(tokens), 1);
}
